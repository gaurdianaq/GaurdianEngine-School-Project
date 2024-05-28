#include "AudioSystem.h"
#include "../../ResourceManager/AudioManager/AudioManager.h"

#define LATENCY_MS (50)
#define DRIFT_MS (1)
#define DEVICE_INDEX (0)

AudioSystem::AudioSystem()
{
	audio = static_cast<Audio*>(audioManager->GetResource("recording"));
	system = audioManager->getSystem();
	nativeRate = audioManager->GetNativeRate();
	driftThreshold = (*nativeRate * DRIFT_MS) / 1000;
	desiredLatency = (*nativeRate * LATENCY_MS) / 1000;
	adjustedLatency = desiredLatency;
	actualLatency = desiredLatency;
	audio->sound->getLength(&soundLength, FMOD_TIMEUNIT_PCM);
	
}

AudioSystem::~AudioSystem()
{

}

FMOD_RESULT result;

void AudioSystem::Process()
{
	audioManager->Update();

	//Determine how much has been recorded since we last checked
	unsigned int recordPos = 0;
	audioManager->getFMODResult(system->getRecordPosition(DEVICE_INDEX, &recordPos));

	static unsigned int lastRecordPos = 0;
	unsigned int recordDelta = (recordPos >= lastRecordPos) ? (recordPos - lastRecordPos) : (recordPos + soundLength - lastRecordPos);
	lastRecordPos = recordPos;
	samplesRecorded += recordDelta;

	static unsigned int minRecordDelta = (unsigned int)-1;
	if (recordDelta && (recordDelta < minRecordDelta))
	{
		minRecordDelta = recordDelta; //Smallest driver granularity seen so far
		adjustedLatency = (recordDelta <= desiredLatency) ? desiredLatency : recordDelta; //Adjust our latency if driver granularity is high
	}

	
	//Delay playback until our desired latency is reached.
	
	if (!audio->channel && samplesRecorded >= adjustedLatency)
	{
		audioManager->getFMODResult(system->playSound(audio->sound, 0, false, &audio->channel));
	}

	if (audio->channel)
	{
		
		//Stop playback if recording stops.
		
		bool isRecording = false;
		audioManager->getFMODResult(system->isRecording(DEVICE_INDEX, &isRecording));

		if (!isRecording)
		{
			audioManager->getFMODResult(audio->channel->setPaused(true));
		}

		
		//Determine how much has been played since we last checked.
		
		unsigned int playPos = 0;
		audioManager->getFMODResult(audio->channel->getPosition(&playPos, FMOD_TIMEUNIT_PCM));

		static unsigned int lastPlayPos = 0;
		unsigned int playDelta = (playPos >= lastPlayPos) ? (playPos - lastPlayPos) : (playPos + soundLength - lastPlayPos);
		lastPlayPos = playPos;
		samplesPlayed += playDelta;

		
		//Compensate for any drift.
		
		int latency = samplesRecorded - samplesPlayed;
		actualLatency = (0.97f * actualLatency) + (0.03f * latency);

		int playbackRate = *nativeRate;
		if (actualLatency < (int)(adjustedLatency - driftThreshold))
		{
			//Play position is catching up to the record position, slow playback down by 2%
			playbackRate = *nativeRate - (*nativeRate / 50);
		}
		else if (actualLatency > (int)(adjustedLatency + driftThreshold))
		{
			//Play position is falling behind the record position, speed playback up by 2%
			playbackRate = *nativeRate + (*nativeRate / 50);
		}

		audioManager->getFMODResult(audio->channel->setFrequency((float)playbackRate));
	}
}
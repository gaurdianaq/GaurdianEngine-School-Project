#include "AudioManager.h"
#include "Audio.h"
#include <iostream>

AudioManager* AudioManager::instance = nullptr;

std::string fmodResultToString(FMOD_RESULT result)
{
	switch (result)
	{
	case FMOD_OK:
		return "FMOD_OK";
		break;
	case FMOD_ERR_BADCOMMAND:
		return "FMOD_ERR_BADCOMMAND";
		break;
	case FMOD_ERR_CHANNEL_ALLOC:
		return "FMOD_ERR_CHANNEL_ALLOC";
		break;
	case FMOD_ERR_CHANNEL_STOLEN:
		return "FMOD_ERR_CHANNEL_STOLEN";
		break;
	case FMOD_ERR_DMA:
		return "FMOD_ERR_DMA";
		break;
	case FMOD_ERR_DSP_CONNECTION:
		return "FMOD_ERR_DSP_CONNECTION";
		break;
	case FMOD_ERR_DSP_DONTPROCESS:
		return "FMOD_ERR_DSP_DONTPROCESS";
		break;
	case FMOD_ERR_DSP_FORMAT:
		return "FMOD_ERR_DSP_FORMAT";
		break;
	case FMOD_ERR_DSP_INUSE:
		return "FMOD_ERR_DSP_INUSE";
		break;
	case FMOD_ERR_DSP_NOTFOUND:
		return "FMOD_ERR_DSP_NOTFOUND";
		break;
	case FMOD_ERR_DSP_RESERVED:
		return "FMOD_ERR_DSP_RESERVED";
		break;
	case FMOD_ERR_DSP_SILENCE:
		return "FMOD_ERR_DSP_SILENCE";
		break;
	case FMOD_ERR_DSP_TYPE:
		return "FMOD_ERR_DSP_TYPE";
		break;
	case FMOD_ERR_FILE_BAD:
		return "FMOD_ERR_FILE_BAD";
		break;
	case FMOD_ERR_FILE_COULDNOTSEEK:
		return "FMOD_ERR_FILE_COULDNOTSEEK";
		break;
	case FMOD_ERR_FILE_DISKEJECTED:
		return "FMOD_ERR_FILE_DISKEJECTED";
		break;
	case FMOD_ERR_FILE_EOF:
		return "FMOD_ERR_FILE_EOF";
		break;
	case FMOD_ERR_FILE_ENDOFDATA:
		return "FMOD_ERR_FILE_ENDOFDATA";
		break;
	case FMOD_ERR_FILE_NOTFOUND:
		return "FMOD_ERR_FILE_NOTFOUND";
		break;
	case FMOD_ERR_FORMAT:
		return "FMOD_ERR_FORMAT";
		break;
	case FMOD_ERR_HEADER_MISMATCH:
		return "FMOD_ERR_HEADER_MISMATCH";
		break;
	case FMOD_ERR_HTTP:
		return "FMOD_ERR_HTTP";
		break;
	case FMOD_ERR_HTTP_ACCESS:
		return "FMOD_ERR_HTTP_ACCESS";
		break;
	case FMOD_ERR_HTTP_PROXY_AUTH:
		return "FMOD_ERR_HTTP_PROXY_AUTH";
		break;
	case FMOD_ERR_HTTP_SERVER_ERROR:
		return "FMOD_ERR_HTTP_SERVER_ERROR";
		break;
	case FMOD_ERR_HTTP_TIMEOUT:
		return "FMOD_ERR_HTTP_TIMEOUT";
		break;
	case FMOD_ERR_INITIALIZATION:
		return "FMOD_ERR_INITIALIZATION";
		break;
	case FMOD_ERR_INITIALIZED:
		return "FMOD_ERR_INITIALIZED";
		break;
	case FMOD_ERR_INTERNAL:
		return "FMOD_ERR_INTERNAL";
		break;
	case FMOD_ERR_INVALID_FLOAT:
		return "FMOD_ERR_INVALID_FLOAT";
		break;
	case FMOD_ERR_INVALID_HANDLE:
		return "FMOD_ERR_INVALID_HANDLE";
		break;
	case FMOD_ERR_INVALID_PARAM:
		return "FMOD_ERR_INVALID_PARAM";
		break;
	case FMOD_ERR_INVALID_POSITION:
		return "FMOD_ERR_INVALID_POSITION";
		break;
	case FMOD_ERR_INVALID_SPEAKER:
		return "FMOD_ERR_INVALID_SPEAKER";
		break;
	case FMOD_ERR_INVALID_SYNCPOINT:
		return "FMOD_ERR_INVALID_SYNCPOINT";
		break;
	case FMOD_ERR_INVALID_THREAD:
		return "FMOD_ERR_INVALID_THREAD";
		break;
	case FMOD_ERR_INVALID_VECTOR:
		return "FMOD_ERR_INVALID_VECTOR";
		break;
	case FMOD_ERR_MAXAUDIBLE:
		return "FMOD_ERR_MAXAUDIBLE";
		break;
	case FMOD_ERR_MEMORY:
		return "FMOD_ERR_MEMORY";
		break;
	case FMOD_ERR_MEMORY_CANTPOINT:
		return "FMOD_ERR_MEMORY_CANTPOINT";
		break;
	case FMOD_ERR_NEEDS3D:
		return "FMOD_ERR_NEEDS3D";
		break;
	case FMOD_ERR_NEEDSHARDWARE:
		return "FMOD_ERR_NEEDSHARDWARE";
		break;
	case FMOD_ERR_NET_CONNECT:
		return "FMOD_ERR_NET_CONNECT";
		break;
	case FMOD_ERR_NET_SOCKET_ERROR:
		return "FMOD_ERR_NET_SOCKET_ERROR";
		break;
	case FMOD_ERR_NET_URL:
		return "FMOD_ERR_NET_URL";
		break;
	case FMOD_ERR_NET_WOULD_BLOCK:
		return "FMOD_ERR_NET_WOULD_BLOCK";
		break;
	case FMOD_ERR_NOTREADY:
		return "FMOD_ERR_NOTREADY";
		break;
	case FMOD_ERR_OUTPUT_ALLOCATED:
		return "FMOD_ERR_OUTPUT_ALLOCATED";
		break;
	case FMOD_ERR_OUTPUT_CREATEBUFFER:
		return "FMOD_ERR_OUTPUT_CREATEBUFFER";
		break;
	case FMOD_ERR_OUTPUT_DRIVERCALL:
		return "FMOD_ERR_OUTPUT_DRIVERCALL";
		break;
	case FMOD_ERR_OUTPUT_FORMAT:
		return "FMOD_ERR_OUTPUT_FORMAT";
		break;
	case FMOD_ERR_OUTPUT_INIT:
		return "FMOD_ERR_OUTPUT_INIT";
		break;
	case FMOD_ERR_OUTPUT_NODRIVERS:
		return "FMOD_ERR_OUTPUT_NODRIVERS";
		break;
	case FMOD_ERR_PLUGIN:
		return "FMOD_ERR_PLUGIN";
		break;
	case FMOD_ERR_PLUGIN_MISSING:
		return "FMOD_ERR_PLUGIN_MISSING";
		break;
	case FMOD_ERR_PLUGIN_RESOURCE:
		return "FMOD_ERR_PLUGIN_RESOURCE";
		break;
	case FMOD_ERR_PLUGIN_VERSION:
		return "FMOD_ERR_PLUGIN_VERSION";
		break;
	case FMOD_ERR_RECORD:
		return "FMOD_ERR_RECORD";
		break;
	case FMOD_ERR_REVERB_CHANNELGROUP:
		return "FMOD_ERR_REVERB_CHANNELGROUP";
		break;
	case FMOD_ERR_REVERB_INSTANCE:
		return "FMOD_ERR_REVERB_INSTANCE";
		break;
	case FMOD_ERR_SUBSOUNDS:
		return "FMOD_ERR_SUBSOUNDS";
		break;
	case FMOD_ERR_SUBSOUND_ALLOCATED:
		return "FMOD_ERR_SUBSOUND_ALLOCATED";
		break;
	case FMOD_ERR_SUBSOUND_CANTMOVE:
		return "FMOD_ERR_SUBSOUND_CANTMOVE";
		break;
	case FMOD_ERR_TAGNOTFOUND:
		return "FMOD_ERR_TAGNOTFOUND";
		break;
	case FMOD_ERR_TOOMANYCHANNELS:
		return "FMOD_ERR_TOOMANYCHANNELS";
		break;
	case FMOD_ERR_TRUNCATED:
		return "FMOD_ERR_TRUNCATED";
		break;
	case FMOD_ERR_UNIMPLEMENTED:
		return "FMOD_ERR_UNIMPLEMENTED";
		break;
	case FMOD_ERR_UNINITIALIZED:
		return "FMOD_ERR_UNINITIALIZED";
		break;
	case FMOD_ERR_UNSUPPORTED:
		return "FMOD_ERR_UNSUPPORTED";
		break;
	case FMOD_ERR_VERSION:
		return "FMOD_ERR_VERSION";
		break;
	case FMOD_ERR_EVENT_ALREADY_LOADED:
		return "FMOD_ERR_EVENT_ALREADY_LOADED";
		break;
	case FMOD_ERR_EVENT_LIVEUPDATE_BUSY:
		return "FMOD_ERR_EVENT_LIVEUPDATE_BUSY";
		break;
	case FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH:
		return "FMOD_ERR_EVENT_LIVEUPDATE_MISMATCH";
		break;
	case FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT:
		return "FMOD_ERR_EVENT_LIVEUPDATE_TIMEOUT";
		break;
	case FMOD_ERR_EVENT_NOTFOUND:
		return "FMOD_ERR_EVENT_NOTFOUND";
		break;
	case FMOD_ERR_STUDIO_UNINITIALIZED:
		return "FMOD_ERR_STUDIO_UNINITIALIZED";
		break;
	case FMOD_ERR_STUDIO_NOT_LOADED:
		return "FMOD_ERR_STUDIO_NOT_LOADED";
		break;
	case FMOD_ERR_INVALID_STRING:
		return "FMOD_ERR_INVALID_STRING";
		break;
	case FMOD_ERR_ALREADY_LOCKED:
		return "FMOD_ERR_ALREADY_LOCKED";
		break;
	case FMOD_ERR_NOT_LOCKED:
		return "FMOD_ERR_NOT_LOCKED";
		break;
	case FMOD_ERR_RECORD_DISCONNECTED:
		return "FMOD_ERR_RECORD_DISCONNECTED";
		break;
	case FMOD_ERR_TOOMANYSAMPLES:
		return "FMOD_ERR_TOOMANYSAMPLES";
		break;
	default:
		return "You managed to break an enum, I hope you're proud...";
		break;
	}
}

FMOD_DSP_TYPE stringToDSPType(std::string type)
{
	if (type == "MIXER")
	{
		return FMOD_DSP_TYPE_MIXER;
	}
	else if (type == "OSCILLATOR")
	{
		return FMOD_DSP_TYPE_OSCILLATOR;
	}
	else if (type == "LOWPASS")
	{
		return FMOD_DSP_TYPE_LOWPASS;
	}
	else if (type == "ITLOWPASS")
	{
		return FMOD_DSP_TYPE_ITLOWPASS;
	}
	else if (type == "HIGHPASS")
	{
		return FMOD_DSP_TYPE_HIGHPASS;
	}
	else if (type == "ECHO")
	{
		return FMOD_DSP_TYPE_ECHO;
	}
	else if (type == "FADER")
	{
		return FMOD_DSP_TYPE_FADER;
	}
	else if (type == "FLANGE")
	{
		return FMOD_DSP_TYPE_FLANGE;
	}
	else if (type == "DISTORTION")
	{
		return FMOD_DSP_TYPE_DISTORTION;
	}
	else if (type == "NORMALIZE")
	{
		return FMOD_DSP_TYPE_NORMALIZE;
	}
	else if (type == "LIMITER")
	{
		return FMOD_DSP_TYPE_LIMITER;
	}
	else if (type == "PARAMEQ")
	{
		return FMOD_DSP_TYPE_PARAMEQ;
	}
	else if (type == "PITCHSHIFT")
	{
		return FMOD_DSP_TYPE_PITCHSHIFT;
	}
	else if (type == "CHORUS")
	{
		return FMOD_DSP_TYPE_CHORUS;
	}
	else if (type == "VSTPLUGIN")
	{
		return FMOD_DSP_TYPE_VSTPLUGIN;
	}
	else if (type == "WINAMPLUGIN")
	{
		return FMOD_DSP_TYPE_WINAMPPLUGIN;
	}
	else if (type == "ITECHO")
	{
		return FMOD_DSP_TYPE_ITECHO;
	}
	else if (type == "COMPRESSOR")
	{
		return FMOD_DSP_TYPE_COMPRESSOR;
	}
	else if (type == "SFXREVERB")
	{
		return FMOD_DSP_TYPE_SFXREVERB;
	}
	else if (type == "LOWPASS_SIMPLE")
	{
		return FMOD_DSP_TYPE_LOWPASS_SIMPLE;
	}
	else if (type == "DELAY")
	{
		return FMOD_DSP_TYPE_DELAY;
	}
	else if (type == "TREMOLO")
	{
		return FMOD_DSP_TYPE_TREMOLO;
	}
	else if (type == "LADSPAPLUGIN")
	{
		return FMOD_DSP_TYPE_LADSPAPLUGIN;
	}
	else if (type == "SEND")
	{
		return FMOD_DSP_TYPE_RETURN;
	}
	else if (type == "RETURN")
	{
		return FMOD_DSP_TYPE_HIGHPASS_SIMPLE;
	}
	else if (type == "HIGHPASS_SIMPLE")
	{
		return FMOD_DSP_TYPE_HIGHPASS_SIMPLE;
	}
	else if (type == "PAN")
	{
		return FMOD_DSP_TYPE_PAN;
	}
	else if (type == "THREE_EQ")
	{
		return FMOD_DSP_TYPE_THREE_EQ;
	}
	else if (type == "FFT")
	{
		return FMOD_DSP_TYPE_FFT;
	}
	else if (type == "LOUDNESS_METER")
	{
		return FMOD_DSP_TYPE_LOUDNESS_METER;
	}
	else if (type == "ENVELOPEFOLLOWER")
	{
		return FMOD_DSP_TYPE_ENVELOPEFOLLOWER;
	}
	else if (type == "CONVOLUTIONREVERB")
	{
		return FMOD_DSP_TYPE_CONVOLUTIONREVERB;
	}
	else if (type == "CHANNELMIX")
	{
		return FMOD_DSP_TYPE_CHANNELMIX;
	}
	else if (type == "TRANSCEIVER")
	{
		return FMOD_DSP_TYPE_TRANSCEIVER;
	}
	else if (type == "OBJECTPAN")
	{
		return FMOD_DSP_TYPE_OBJECTPAN;
	}
	else if (type == "MULTIBAND_EQ")
	{
		return FMOD_DSP_TYPE_MULTIBAND_EQ;
	}
	else if (type == "MAX")
	{
		return FMOD_DSP_TYPE_MAX;
	}

	return FMOD_DSP_TYPE_UNKNOWN;
}

void AudioManager::getFMODResult(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << fmodResultToString(result) << std::endl;
	}
}

AudioManager* AudioManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new AudioManager();
	}
	return instance;
}

AudioManager::AudioManager()
{
	getFMODResult(FMOD::System_Create(&system));
	getFMODResult(system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr));
	channelGroups["master"] = new ChannelGroup(); //assign the master channel to the channelgroups map
	getFMODResult(system->getMasterChannelGroup(&channelGroups["master"]->channelGroup)); //actually get the master channel from fmod
	channelRegisterCount = 0;
	isRecording = false;
	Init();
}

AudioManager::~AudioManager()
{
	//cleanup
	getFMODResult(system->close());
	getFMODResult(system->release());
}

void AudioManager::Init()
{
	deserializer.DeserializeJson("fmodconfig.json", this);
	nativeRate = 0;
	nativeChannels = 0;
	getFMODResult(system->getRecordDriverInfo(0, NULL, 0, NULL, &nativeRate, NULL, &nativeChannels, NULL));
	exinfo = { 0 };
	exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	exinfo.numchannels = nativeChannels;
	exinfo.format = FMOD_SOUND_FORMAT_PCM16;
	exinfo.defaultfrequency = nativeRate;
	exinfo.length = nativeRate * sizeof(short) * nativeChannels; /* 1 second buffer, size here doesn't change latency */

}

void AudioManager::Update()
{
	getFMODResult(system->update());
}

bool AudioManager::LoadResource(Resource* resource)
{
	Audio* audio = static_cast<Audio*>(resource);
	//uses bitwise or to assign the mode
	if (audio->type == AudioType::Stream)
	{
		audio->mode |= FMOD_CREATESTREAM;
	}
	else if (audio->type == AudioType::Sample)
	{
		audio->mode |= FMOD_CREATESAMPLE;
	}
	else if (audio->type == AudioType::NetStream)
	{
		audio->mode |= FMOD_CREATESTREAM;
		audio->mode |= FMOD_NONBLOCKING;
	}
	else if (audio->type == AudioType::Recording)
	{
		audio->mode |= FMOD_LOOP_NORMAL;
		audio->mode |= FMOD_OPENUSER;
	}
	if (audio->is3D)
	{
		audio->mode |= FMOD_3D;
	}
	else
	{
		audio->mode |= FMOD_2D;
	}

	if (audio->type != AudioType::NetStream) //ignore this flag if the type is a netstream
	{
		if (audio->loops)
		{
			audio->mode |= FMOD_LOOP_NORMAL;
		}
		else
		{
			audio->mode |= FMOD_LOOP_OFF;
		}
	}
	
	if (audio->type != AudioType::Recording)
	{
		getFMODResult(system->createSound(audio->filePath.c_str(), audio->mode, nullptr, &audio->sound));
	}
	else
	{
		getFMODResult(system->createSound(audio->filePath.c_str(), audio->mode, &exinfo, &audio->sound));
	}
	resources[audio->friendlyName] = audio;
	getFMODResult(system->playSound(audio->sound, nullptr, audio->isPaused, &audio->channel));
	getFMODResult(audio->channel->setChannelGroup(channelGroups[audio->channelGroupName]->channelGroup));
	return true;
}

void AudioManager::UnloadAudio(std::string audioName)
{
	static_cast<Audio*>(resources[audioName])->sound->release();
	resources.erase(audioName);
}

void AudioManager::CreateChannelGroup(std::string channelGroupName)
{
	channelGroups[channelGroupName] = new ChannelGroup();
	getFMODResult(system->createChannelGroup(channelGroupName.c_str(), &channelGroups[channelGroupName]->channelGroup));
	getFMODResult(channelGroups["master"]->channelGroup->addGroup(channelGroups[channelGroupName]->channelGroup));
}

void AudioManager::PlaySound(std::string soundName)
{
	Audio* audio = static_cast<Audio*>(resources[soundName]);

	getFMODResult(system->playSound(audio->sound, nullptr, false, &audio->channel));
}

void AudioManager::TogglePause(std::string soundName)
{
	Audio* audio = static_cast<Audio*>(resources[soundName]);
	getFMODResult(audio->channel->getPaused(&audio->isPaused));
	getFMODResult(audio->channel->setPaused(!audio->isPaused));
}

FMOD::System* AudioManager::getSystem()
{
	return system;
}

void AudioManager::ToggleRecording(std::string soundName)
{
	Audio* recording = static_cast<Audio*>(resources[soundName]);
	getFMODResult(system->getRecordNumDrivers(NULL, &numRecordingDevices));
	if (numRecordingDevices == 0)
	{
		printf("No recording devices detected!\n");
		return;
	}
	if (!isRecording)
	{
		getFMODResult(system->recordStart(0, recording->sound, true));
		getFMODResult(system->playSound(recording->sound, nullptr, false, &recording->channel));
		AddChannelToChannelGroup("recording", "recordingGroup");
		isRecording = true;
	}
	else
	{
		getFMODResult(system->recordStop(0));
		getFMODResult(recording->channel->stop());
		isRecording = false;
	}
	
}

void AudioManager::AddChannelToChannelGroup(std::string soundName, std::string groupName)
{
	Audio* audio = static_cast<Audio*>(resources[soundName]);

	if (channelGroups[groupName] != nullptr)
	{
		getFMODResult(audio->channel->setChannelGroup(channelGroups[groupName]->channelGroup));
	}
	else
	{
		std::cout << "Channel Group " << groupName << " does not exist!" << std::endl;
	}
}

void AudioManager::AdjustSoundVolume(std::string soundName, float volumeAdjust)
{
	Audio* audio = static_cast<Audio*>(resources[soundName]);
	if (audio->volume > 0.01f && volumeAdjust < 0.0f)
	{
		audio->volume += volumeAdjust;
	}
	else if (audio->volume < 1.0f && volumeAdjust > 0.0f)
	{
		audio->volume += volumeAdjust;
	}
	getFMODResult(audio->channel->setVolume(audio->volume));
}

void AudioManager::AdjustSoundPitch(std::string soundName, float pitchAdjust)
{
	Audio* audio = static_cast<Audio*>(resources[soundName]);
	if (audio->pitch > 0.5f && pitchAdjust < 0.0f)
	{
		audio->pitch += pitchAdjust;
	}
	else if (audio->pitch < 2.0f && pitchAdjust > 0.0f)
	{
		audio->pitch += pitchAdjust;
	}
	getFMODResult(audio->channel->setPitch(audio->pitch));
}

int* AudioManager::GetNativeRate()
{
	return &nativeRate;
}

void AudioManager::AdjustSoundBalance(std::string soundName, float balanceAdjust)
{
	Audio* audio = static_cast<Audio*>(resources[soundName]);
	if (audio->pan > -0.99f && balanceAdjust < 0)
	{
		audio->pan += balanceAdjust;
	}
	else if (audio->pan < 1.0f && balanceAdjust > 0)
	{
		audio->pan += balanceAdjust;
	}
	getFMODResult(audio->channel->setPan(audio->pan));
}

void AudioManager::AdjustChannelGroupVolume(std::string channelGroupName, float volumeAdjust)
{
	if (channelGroups[channelGroupName]->volume > 0.01f && volumeAdjust < 0.0f)
	{
		channelGroups[channelGroupName]->volume += volumeAdjust;
	}
	else if (channelGroups[channelGroupName]->volume < 1.0f && volumeAdjust > 0.0f)
	{
		channelGroups[channelGroupName]->volume += volumeAdjust;
	}
	getFMODResult(channelGroups[channelGroupName]->channelGroup->setVolume(channelGroups[channelGroupName]->volume));
}

void AudioManager::AdjustChannelGroupPitch(std::string channelGroupName, float pitchAdjust)
{
	if (channelGroups[channelGroupName]->pitch > 0.5f && pitchAdjust < 0.0f)
	{
		channelGroups[channelGroupName]->pitch += pitchAdjust;
	}
	else if (channelGroups[channelGroupName]->pitch < 2.0f && pitchAdjust > 0.0f)
	{
		channelGroups[channelGroupName]->pitch += pitchAdjust;
	}
	getFMODResult(channelGroups[channelGroupName]->channelGroup->setPitch(channelGroups[channelGroupName]->pitch));
}

void AudioManager::AdjustChannelGroupBalance(std::string channelGroupName, float balanceAdjust)
{
	if (channelGroups[channelGroupName]->pan > -0.99f && balanceAdjust < 0.0f)
	{
		channelGroups[channelGroupName]->pan += balanceAdjust;
	}
	else if (channelGroups[channelGroupName]->pan < 1.0f && balanceAdjust > 0.0f)
	{
		channelGroups[channelGroupName]->pan += balanceAdjust;
	}
	getFMODResult(channelGroups[channelGroupName]->channelGroup->setPan(channelGroups[channelGroupName]->pan));
}

void AudioManager::ToggleDSP(std::string dspName)
{
	if (dspsByName[dspName] != nullptr)
	{
		getFMODResult(dspsByName[dspName]->dsp->setBypass(!dspsByName[dspName]->isBypassed));
		getFMODResult(dspsByName[dspName]->dsp->getBypass(&dspsByName[dspName]->isBypassed));
	}
}

void AudioManager::CreateDSP(std::string dspName, FMOD_DSP_TYPE dspType, bool isActive)
{
	dspsByName[dspName] = new DSP();
	dspsByName[dspName]->isBypassed = isActive;
	getFMODResult(system->createDSPByType(dspType, &dspsByName[dspName]->dsp));
}

void AudioManager::AddDSPToChannelGroup(std::string dspName, std::string channelGroupName)
{
	getFMODResult(channelGroups[channelGroupName]->channelGroup->addDSP(0, dspsByName[dspName]->dsp));
	getFMODResult(dspsByName[dspName]->dsp->setBypass(dspsByName[dspName]->isBypassed));
}

void AudioManager::Deserialize(Document& document)
{
	const Value& ChannelGroups = document["ChannelGroups"];
	const Value& DSPs = document["DSPs"];

	for (Value::ConstValueIterator it = ChannelGroups.Begin(); it != ChannelGroups.End(); ++it)
	{
		CreateChannelGroup((*it)["channelGroupName"].GetString());
	}

	for (Value::ConstValueIterator it = DSPs.Begin(); it != DSPs.End(); ++it)
	{
		CreateDSP((*it)["dspName"].GetString(), stringToDSPType((*it)["dspType"].GetString()), (*it)["isBypassed"].GetBool());
		AddDSPToChannelGroup((*it)["dspName"].GetString(), (*it)["channelGroup"].GetString());
	}
}
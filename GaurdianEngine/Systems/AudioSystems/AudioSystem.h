#ifndef _AUDIO_SYSTEM_HG
#define _AUDIO_SYSTEM_HG

#include "../EntitySystem.h"
#include "../../ResourceManager/AudioManager/Audio.h"
//does nothing currently... might delete it if I can't think of a use for it
class AudioSystem : public EntitySystem
{
public:
	AudioSystem();
	~AudioSystem();
	void Process();
	Audio* audio;
	FMOD_TAG tag;
	FMOD::System* system;
	FMOD_OPENSTATE openState;
	bool starving;
	unsigned int percentage;
	unsigned int samplesRecorded;
	unsigned int samplesPlayed;
	unsigned int adjustedLatency;
	unsigned int desiredLatency;
	unsigned int driftThreshold;
	unsigned int soundLength;
	int* nativeRate;
	int actualLatency;
};

#endif
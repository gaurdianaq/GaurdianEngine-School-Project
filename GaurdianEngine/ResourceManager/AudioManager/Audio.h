#ifndef _AUDIO_HG
#define _AUDIO_HG

#include "../Resource.h"
#include <fmod/fmod.hpp>
#include "AudioType.h"

class Audio : public Resource
{
	friend class AudioManager;
public:
	Audio();
	Audio(AudioType _type, FMOD_MODE _mode, std::string _filePath, std::string _friendlyName);
	~Audio();
	AudioType type;
	bool is3D;
	bool loops;
	FMOD::Sound* sound;
	FMOD::Channel* channel;
	std::string channelGroupName;
	bool isPaused;
	float pan;
	float pitch;
	float volume;
protected:
	FMOD_MODE mode; //configuration details needed for fmod
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _resourceType;
};

#endif
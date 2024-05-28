#ifndef _AUDIO_COMPONENT_HG
#define _AUDIO_COMPONENT_HG

#include "../Core/Component.h"

//will be used to associate audio with a location in space... like it's attached to an entity
//will also be used so the various systems know what sound to play if appropriate (like if two entities collide)
class AudioComponent : public Component
{
public:
	AudioComponent();
	~AudioComponent();
	std::string soundName;
	//bool isPlaying; //not sure if I need this
	bool playOnLoad;
	bool is3D; //if the audio is
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _componentType;
};

#endif
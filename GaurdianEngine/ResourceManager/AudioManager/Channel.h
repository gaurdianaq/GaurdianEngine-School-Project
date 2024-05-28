#ifndef _CHANNEL_HG
#define _CHANNEL_HG

#include <fmod/fmod.hpp>
#include <string>

class Channel
{
public:
	Channel();
	~Channel();
	bool isInUse; //does this channel have a sound or stream assigned to it
	bool isPaused;
	float pan;
	float pitch;
	float volume;
	FMOD::Channel* channel;
};

#endif
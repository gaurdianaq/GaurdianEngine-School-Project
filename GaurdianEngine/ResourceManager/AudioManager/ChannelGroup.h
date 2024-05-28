#ifndef _CHANNEL_GROUP_HG
#define _CHANNEL_GROUP_HG

#include <fmod/fmod.hpp>
#include <vector>
#include "Channel.h"

class ChannelGroup
{
public:
	ChannelGroup();
	~ChannelGroup();
	bool isPaused;
	float pan;
	float pitch;
	float volume;
	FMOD::ChannelGroup* channelGroup;
};

#endif // !_CHANNEL_GROUP_HG

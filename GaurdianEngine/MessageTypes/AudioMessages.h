#ifndef _AUDIO_MESSAGES_HG
#define _AUDIO_MESSAGES_HG

#include "../Core/Message.h"


//data needed to access either a specific sound or channel group
struct AudioMessage : public iMessageData
{
	AudioMessage(std::string _soundName, std::string _channelGroupName);
	std::string soundName;
	std::string channelGroupName;
};

//message to contain data for adjusting something
//could be volume, pitch, frequency
struct AudioAdjustMessage : public iMessageData
{
	AudioAdjustMessage(float _adjustValue);
	float adjustValue;
};

//message to toggle something, stores the name of whatever it is you're toggling (could be a dsp or something else)
struct ToggleMessage : public iMessageData
{
	ToggleMessage(std::string _Name);
	std::string Name;
};

#endif
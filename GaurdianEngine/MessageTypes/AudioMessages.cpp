#include "AudioMessages.h"

AudioMessage::AudioMessage(std::string _soundName, std::string _channelGroupName)
{
	soundName = _soundName;
	channelGroupName = _channelGroupName;
}

AudioAdjustMessage::AudioAdjustMessage(float _adjustValue)
{
	adjustValue = _adjustValue;
}

ToggleMessage::ToggleMessage(std::string _Name)
{
	Name = _Name;
}
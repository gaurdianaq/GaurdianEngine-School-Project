#ifndef _AUDIO_MESSAGE_SYSTEM_HG
#define _AUDIO_MESSAGE_SYSTEM_HG

#include "../MessageSystem.h"

//receives messages which are used to call the audio manager
class AudioMessageSystem : public MessageSystem
{
public:
	AudioMessageSystem();
	~AudioMessageSystem();
protected:
	void ProcessMessages();
private:
	std::string selectedChannelGroup;
	std::string selectedSound;
};

#endif
#ifndef _MESSAGE_SYSTEM_HG
#define _MESSAGE_SYSTEM_HG

#include "../Core/System.h"
#include "../Core/MessageReceiver.h"

//a system for processing messages, is registered and receives messages from the mediator
class MessageSystem : public System, public MessageReceiver
{
public:
	void Process();
protected:
	virtual void ProcessMessages() = 0;
};

#endif
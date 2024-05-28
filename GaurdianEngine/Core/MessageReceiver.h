#ifndef _MESSAGE_RECEIVER_HG
#define _MESSAGE_RECEIVER_HG

#include "Message.h"
#include <queue>

//interface for classes that can receive messages
class MessageReceiver
{
public:
	void ReceiveMessage(Message message);
protected:
	std::queue<Message> messages;
	virtual void ProcessMessages() = 0;
};

#endif // !_MESSAGE_RECEIVER_HG

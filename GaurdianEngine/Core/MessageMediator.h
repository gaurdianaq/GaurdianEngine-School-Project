#ifndef _MEDIATOR_HG
#define _MEDIATOR_HG

#include <queue>
#include <unordered_map>
#include "iMessageSender.h"
#include "MessageReceiver.h"

//receives messages and forwards them to the appropriate messagereceiver
class MessageMediator : public iMessageSender
{
public:
	static MessageMediator* Instance();
	void RegisterReceiver(std::string receiverName, MessageReceiver* receiver);
	void ProcessMessages();
	void SendMessage(Message message);
private:
	static MessageMediator* instance;
	MessageMediator();
	std::unordered_map<std::string, MessageReceiver*> messageReceivers;
	std::queue<Message> messages;
};

#define mediator MessageMediator::Instance()

#endif
#include "MessageMediator.h"

MessageMediator* MessageMediator::Instance()
{
	if (instance == nullptr)
	{
		instance = new MessageMediator();
	}

	return instance;
}

MessageMediator* MessageMediator::instance;

MessageMediator::MessageMediator()
{

}

void MessageMediator::RegisterReceiver(std::string receiverName, MessageReceiver* receiver)
{
	messageReceivers[receiverName] = receiver;
}

//message is pushed onto a queue of messages to be sent
void MessageMediator::SendMessage(Message message)
{
	messages.push(message);
}

//go's through all the messages and sends them to the appropriate receiver
void MessageMediator::ProcessMessages()
{
	for (int i = 0; i < messages.size(); ++i)
	{
		messageReceivers[messages.front().messageTarget]->ReceiveMessage(messages.front());
		messages.pop();
	}
}


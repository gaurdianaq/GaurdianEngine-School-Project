#include "MessageReceiver.h"

void MessageReceiver::ReceiveMessage(Message message)
{
	messages.push(message);
}
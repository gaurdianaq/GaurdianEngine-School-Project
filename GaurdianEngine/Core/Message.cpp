#include "Message.h"

iMessageData::~iMessageData()
{

}

Message::Message(std::string _messageName, std::string _messageTarget, iMessageData* _messageData)
{
	messageName = _messageName;
	messageTarget = _messageTarget;
	messageData = _messageData;
}
#ifndef _COMMAND_HG
#define _COMMAND_HG

#include <string>

//Pure Virtual class that will act as base class for messagedata (a little less messy than using a void* will ensure anything passed will be intended to be message data
struct iMessageData
{
	virtual ~iMessageData() = 0;
};

struct Message
{
	Message(std::string _messageName, std::string _messageTarget, iMessageData* messageData);
	std::string messageName;
	std::string messageTarget;
	iMessageData* messageData;
};

#endif _COMMAND_HG
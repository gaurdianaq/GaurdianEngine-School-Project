#ifndef _IMEDIATOR_HG
#define _IMEDIATOR_HG

#include "Message.h"

//pure virtual interface that says a class can send messages through the system
//also prevents classes from accessing the actual mediator
class iMessageSender
{
public:
	virtual void SendMessage(Message message) = 0;
};

#endif // !_IMEDIATOR_HG

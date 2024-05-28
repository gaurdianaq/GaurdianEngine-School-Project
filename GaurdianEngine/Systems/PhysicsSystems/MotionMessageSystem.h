#ifndef _MOTION_MESSAGE_SYSTEM_HG
#define _MOTION_MESSAGE_SYSTEM_HG

#include "../MessageSystem.h"

//handles any messages related to motion
//example if a message was sent to change the velocity of an object after a collision
class MotionMessageSystem : public MessageSystem
{
protected:
	void ProcessMessages();
};

#endif
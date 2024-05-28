#ifndef _COLLISION_RESPONSE_SYSTEM_HG
#define _COLLISION_RESPONSE_SYSTEM_HG

#include "../MessageSystem.h"
#include "../../Core/iMessageSender.h"

class CollisionResponseSystem : public MessageSystem
{
public:
	CollisionResponseSystem();
	~CollisionResponseSystem();
	void SetMsgSender(iMessageSender* _msgSender);
protected:
	void ProcessMessages();
private:
	iMessageSender* msgSender;
};

#endif
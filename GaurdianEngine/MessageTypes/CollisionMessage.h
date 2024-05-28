#ifndef _COLLISION_MESSAGE_HG
#define _COLLISION_MESSAGE_HG

#include "../Core/Message.h"
#include "../Core/Entity.h"

struct CollisionMessage : public iMessageData
{
	CollisionMessage(Entity* _entity1, Entity* _entity2);
	Entity* entity1;
	Entity* entity2;
};

#endif
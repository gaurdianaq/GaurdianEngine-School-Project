#ifndef _ENTITY_SYSTEM_HG
#define _ENTITY_SYSTEM_HG

#include "../Core/System.h"
#include "../Core/Entity.h"

//system that processes a vector of entities
class EntitySystem : public System
{
protected:
	std::vector<Entity*>* entitiesToProcess;
};

#endif
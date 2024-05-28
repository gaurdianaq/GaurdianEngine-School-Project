#ifndef _COLLISION_SYSTEM_HG
#define _COLLISION_SYSTEM_HG

#include "../../Core/System.h"
#include "../../Core/iMessageSender.h"
#include "../../Components/Transform.h"
#include "../../Components/Collider.h"

#define HGRID_MAX_LEVELS 5
#define NUM_BUCKETS 1024

class CollideableHierarchyObject
{
public:
	CollideableHierarchyObject* nextObject;
	Transform transform;
	Collider* collider;
	int bucket; //hash bucket index
	int level; // grid level for the object
	int ComputerHashTableBucket();
};

class HGrid {
public:
	unsigned int occupiedLevelsMask;
	int objectsAtLevel[HGRID_MAX_LEVELS];
	CollideableHierarchyObject* objectBucket[NUM_BUCKETS];
	int timeStamp[NUM_BUCKETS];
	int tick;
	void AddObjectToHGrid(CollideableHierarchyObject* obj);
};

class CollisionSystem : public System
{
public:
	CollisionSystem();
	~CollisionSystem();
	void Process();
	void SetMsgSender(iMessageSender* _msgSender);
private:
	void CheckCollision(Entity* collider1, Entity* collider2);
	iMessageSender* msgSender;
};

#endif // !_COLLISION_SYSTEM_HG

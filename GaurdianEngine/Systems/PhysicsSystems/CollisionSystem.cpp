#include "CollisionSystem.h"
#include "../../Components/BoxCollider.h"
#include "../../Components/SphereCollider.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../MessageTypes/CollisionMessage.h"
#include "../../Core/SceneManager.h"

#define MIN_CELL_SIZE 10.0f

int CollideableHierarchyObject::ComputerHashTableBucket()
{
	const int h1 = 0x8da6b343;
	const int h2 = 0xd8163841;
	const int h3 = 0xcb1ab31f;

	int n = h1 * transform.position.x + h2 * transform.position.y + h3 * transform.position.z;
	n = n % NUM_BUCKETS;
	if (n < 0) n += NUM_BUCKETS;
	return n;
}

void HGrid::AddObjectToHGrid(CollideableHierarchyObject* obj)
{
	int level;
	float size = MIN_CELL_SIZE;
	//float diameter = 
}

CollisionSystem::CollisionSystem()
{
	//entitiesToProcess = sceneManager->GetEntityByComponent("Collider");
}

CollisionSystem::~CollisionSystem()
{

}

//this is so awful I hate it XD, want to implement more efficient checking asasp
void CollisionSystem::Process()
{
	/*
	//currently just cycles through every object that has a collider...
	//will soon be implementing broad/narrow phase collision detection
	for (int i = 0; i < entitiesToProcess->size(); ++i)
	{
		Collider* collider1 = static_cast<Collider*>(entitiesToProcess->at(i)->GetComponent("Collider"));
		if (collider1 != nullptr)
		{
			for (int n = 0; n < entitiesToProcess->size(); ++n)
			{
				Collider* collider2 = static_cast<Collider*>(entitiesToProcess->at(n)->GetComponent("Collider"));
				if (collider2 != nullptr)
				{
					if (collider2 != collider1)
					{
						CheckCollision(entitiesToProcess->at(i), entitiesToProcess->at(n));
					}
				}
			}
		}
	}*/
}

void CollisionSystem::SetMsgSender(iMessageSender* _msgSender)
{
	msgSender = _msgSender;
}

void CollisionSystem::CheckCollision(Entity* entity1, Entity* entity2)
{
	//gets the collider components from the entities being tested
	Collider* collider1 = static_cast<Collider*>(entity1->GetComponent("Collider"));
	Collider* collider2 = static_cast<Collider*>(entity2->GetComponent("Collider"));
	//does a dynamic cast to see which type of entity it is
	BoxCollider* bCollider1 = dynamic_cast<BoxCollider*>(collider1);
	SphereCollider* sCollider1 = dynamic_cast<SphereCollider*>(collider1);
	BoxCollider* bCollider2 = dynamic_cast<BoxCollider*>(collider2);
	SphereCollider* sCollider2 = dynamic_cast<SphereCollider*>(collider2);
	Transform* transform1 = static_cast<Transform*>(entity1->GetComponent("Transform"));
	Transform* transform2 = static_cast<Transform*>(entity2->GetComponent("Transform"));

	//going to be a big ass if statement checking which types are being tested against, until I figure out a cleaner way to do this
	if (!collider1->collided && !collider2->collided)
	{
		if (bCollider1 != nullptr && bCollider2 != nullptr)
		{

		}
		else if (bCollider1 != nullptr && sCollider2 != nullptr)
		{

		}
		else if (sCollider1 != nullptr && sCollider2 != nullptr)
		{
			if (glm::distance(transform1->position, transform2->position) < (sCollider1->radius + sCollider2->radius))
			{
				collider1->collided = true; //sets collided to true so doesn't keep checking for collision until the response has been processed
				collider2->collided = true;
				msgSender->SendMessage(Message("Collision", "CollisionResponse", new CollisionMessage(entity1, entity2))); //sends a message with pointers to the two objects that collided
			}
		}
		else if (sCollider1 != nullptr && bCollider2 != nullptr)
		{

		}
	}
}
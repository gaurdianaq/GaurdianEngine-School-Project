#include "CollisionResponseSystem.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Components/Collider.h"
#include "../../MessageTypes/CollisionMessage.h"

CollisionResponseSystem::CollisionResponseSystem()
{

}

CollisionResponseSystem::~CollisionResponseSystem()
{

}

void CollisionResponseSystem::ProcessMessages()
{
	for (int i = 0; i < messages.size(); ++i)
	{
		CollisionMessage* message = static_cast<CollisionMessage*>(messages.front().messageData);
		Entity* entity1 = message->entity1;
		Entity* entity2 = message->entity2;
		delete messages.front().messageData; //deletes the message now that we have the data from it
		Transform* transform1 = static_cast<Transform*>(entity1->GetComponent("Transform"));
		Transform* transform2 = static_cast<Transform*>(entity2->GetComponent("Transform"));
		Velocity* velocity1 = static_cast<Velocity*>(entity1->GetComponent("Velocity"));
		Velocity* velocity2 = static_cast<Velocity*>(entity2->GetComponent("Velocity"));
		Collider* collider1 = static_cast<Collider*>(entity1->GetComponent("Collider"));
		Collider* collider2 = static_cast<Collider*>(entity2->GetComponent("Collider"));
		if (velocity1 != nullptr) //if the object has a velocity component, calculate the appropriate response
		{
			/*
			velocity1->currentVelocity.y = !velocity1->currentVelocity.y;
			velocity1->currentVelocity.z = !velocity1->currentVelocity.z;
			velocity1->currentVelocity.x = !velocity1->currentVelocity.x;
			*/

			if (transform1->position.y >= transform2->position.y)
			{
				velocity1->currentVelocity = glm::reflect(velocity1->currentVelocity, glm::vec3(0, 1, 0));
			}
			else
			{
				velocity1->currentVelocity = glm::reflect(velocity1->currentVelocity, glm::vec3(0, -1, 0));
			}
			
		}
		if (velocity2 != nullptr) //if the object has a velocity component, calculate the appropriate response
		{
			/*
			velocity2->currentVelocity.y = !velocity2->currentVelocity.y;
			velocity2->currentVelocity.z = !velocity2->currentVelocity.z;
			velocity2->currentVelocity.x = !velocity2->currentVelocity.x;
			*/
			if (transform2->position.y >= transform1->position.y)
			{
				velocity2->currentVelocity = glm::reflect(velocity2->currentVelocity, glm::vec3(0, 1, 0));
			}
			else
			{
				velocity2->currentVelocity = glm::reflect(velocity2->currentVelocity, glm::vec3(0, 1, 0));
			}
			
		}
		collider1->collided = false; //sets collided to false now that the response has been processed and it will check for collision again
		collider2->collided = false;
		messages.pop();
	}
}

void CollisionResponseSystem::SetMsgSender(iMessageSender* _msgSender)
{
	msgSender = _msgSender;
}
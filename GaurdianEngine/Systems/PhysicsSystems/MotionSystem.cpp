#include "MotionSystem.h"
#include <GLFW/glfw3.h>
#include "../../Core/SceneManager.h"
#include "../../Components/Transform.h"
#include "../../Components/Acceleration.h"
#include "../../Components/Velocity.h"
#include "../../Components/RigidBody.h"

MotionSystem::MotionSystem()
{
	lastTime = glfwGetTime();
	entitiesToProcess = sceneManager->GetEntityByComponent("RigidBody"); //get all entities that contain a rigidbody
}

MotionSystem::~MotionSystem()
{

}

void MotionSystem::Process()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	if (deltaTime > maxDeltaTime)
	{
		deltaTime = maxDeltaTime;
	}

	for (int i = 0; i < entitiesToProcess->size(); ++i)
	{
		Transform* transform = static_cast<Transform*>(entitiesToProcess->at(i)->GetComponent("Transform"));
		Acceleration* acceleration = static_cast<Acceleration*>(entitiesToProcess->at(i)->GetComponent("Acceleration"));
		Velocity* velocity = static_cast<Velocity*>(entitiesToProcess->at(i)->GetComponent("Velocity"));
		RigidBody* rigidBody = static_cast<RigidBody*>(entitiesToProcess->at(i)->GetComponent("RigidBody"));

		//checks the absolute value of the velocity to ensure it doesn't exceed that in positive or negative
		if (acceleration != nullptr)
		{
			if (fabsf(velocity->currentVelocity.x) < fabsf(velocity->maxVelocity.x))
			{
				velocity->currentVelocity.x += (acceleration->currentAcceleration.x * deltaTime);
			}
			//if (fabsf(velocity->currentVelocity.y) < fabsf(velocity->maxVelocity.y))
			//{
				velocity->currentVelocity.y += (acceleration->currentAcceleration.y * deltaTime);
			//}
			if (fabsf(velocity->currentVelocity.z) < fabsf(velocity->maxVelocity.z))
			{
				velocity->currentVelocity.z += (acceleration->currentAcceleration.z * deltaTime);
			}
			acceleration->currentAcceleration.y -= rigidBody->mass * deltaTime;
		}

		transform->position.x += velocity->currentVelocity.x * deltaTime;
		transform->position.y += velocity->currentVelocity.y * deltaTime;
		transform->position.z += velocity->currentVelocity.z * deltaTime;

		//using icky hard coded values for radius due to time crunch and need to show collisions can happen
		if (transform->position.y + 1 <= -10)
		{
			velocity->currentVelocity = glm::reflect(velocity->currentVelocity, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (transform->position.x - 1 <= -10)
		{
			velocity->currentVelocity.x = fabs(velocity->currentVelocity.x);
		}
		else if (transform->position.x + 1 >= 10)
		{
			velocity->currentVelocity.x = !fabs(velocity->currentVelocity.x);
		}
		if (transform->position.z - 1 <= -10)
		{
			velocity->currentVelocity.z = fabs(velocity->currentVelocity.z);
		}
		else if (transform->position.x + 1 >= 10)
		{
			velocity->currentVelocity.z = !fabs(velocity->currentVelocity.z);
		}
		

		/*
		//if the object go's below the current map boundaries (in this case that's 0) it will despawn the object
		if (transform->position.y < 0)
		{
			sceneManager->Destroy(entitiesToProcess->at(i));
		}
		*/
	}

	lastTime = currentTime;
}
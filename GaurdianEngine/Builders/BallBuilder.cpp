#include "BallBuilder.h"
#include "../Core/Entity.h"
#include "../Core/SceneManager.h"
#include "../Components/Transform.h"
#include "../Components/MeshComponent.h"
#include "../Components/Acceleration.h"
#include "../Components/Velocity.h"
#include "../Components/RigidBody.h"
#include "../ResourceManager/ResourceManager.h"
#include "../ResourceManager/MeshManager/Mesh.h"
#include "../MessageTypes/BuilderMessages.h"

void BallBuilder::Build(iMessageData* data)
{
	BuildBallData* ballData = static_cast<BuildBallData*>(data);
	Entity* ball = new Entity();
	ball->objectName = ballData->ballName;
	Transform* transform = new Transform();
	transform->position = ballData->position;
	transform->scale = glm::vec3(ballData->ballSize);
	Mesh* mesh = static_cast<Mesh*>(resourceManager->GetResource("Mesh", "ball"));//assumes that mesh ball has been loaded already, might change that later
	MeshComponent* meshComponent = new MeshComponent();
	meshComponent->vao_id = mesh->vao_id;
	meshComponent->numIndices = mesh->indices.size();
	meshComponent->materialDiffuse = ballData->ballDiffuse;
	meshComponent->materialSpecular = ballData->ballSpecular;
	meshComponent->meshName = "ball";
	RigidBody* rigidbody = new RigidBody();
	rigidbody->mass = ballData->ballWeight;
	Acceleration* acceleration = new Acceleration();
	acceleration->currentAcceleration = ballData->acceleration;
	Velocity* velocity = new Velocity();
	velocity->maxVelocity = ballData->maxVelocity;
	ball->AddComponent(transform);
	ball->AddComponent(rigidbody);
	ball->AddComponent(acceleration);
	ball->AddComponent(velocity);
	ball->AddComponent(meshComponent);
	sceneManager->Instantiate(ball);
	delete data; //since the data has finally been processed it can be safely deleted
}
#include "TempSceneInit.h"
#include "../../Headers/ComponentTypes.h"
#include "../../Core/Engine.h"


//this will eventually be replaced with the sceneloader
void TempSceneInit::Init()
{
	{
		Entity* camera = new Entity();
		camera->objectName = "mainCamera";
		camera->AddComponent(componentFactory->createComponent("Camera"));
		sceneManager->SetActiveCamera(camera);
		sceneManager->Instantiate(camera);
	}

	{
		Entity* entity = new Entity();
		entity->objectName = "white light";
		Transform* transform = static_cast<Transform*>(componentFactory->createComponent("Transform"));
		transform->position = glm::vec3(500.0f, 500.0f, 0.0f);
		Light* light = static_cast<Light*>(componentFactory->createComponent("Light"));
		light->atten = glm::vec4(0.0f, 0.001f, 0.0f, 0.0f);
		light->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		entity->AddComponent(transform);
		entity->AddComponent(light);
		sceneManager->Instantiate(entity);
	}
	{
		Entity* entity = new Entity();
		entity->objectName = "Ship";
		Transform* transform = static_cast<Transform*>(componentFactory->createComponent("Transform"));
		transform->position.x = 0;
		transform->position.y = 7.5f;
		transform->position.z = -75.0f;
		transform->postRotation.x = glm::radians(90.0f);
		//transform->postRotation.z = glm::radians(90.0f);
		transform->scale = glm::vec3(5);
		MeshComponent* meshComponent = static_cast<MeshComponent*>(componentFactory->createComponent("Mesh"));
		meshComponent->meshName = "plane";
		meshComponent->colour = glm::vec3(1, 0, 0);
		Mesh* mesh = static_cast<Mesh*>(ResourceEngine::Instance()->GetGameResource("Mesh", meshComponent->meshName));
		meshComponent->vao_id = mesh->vao_id;
		meshComponent->numIndices = mesh->indices.size();
		entity->AddComponent(transform);
		entity->AddComponent(meshComponent);
		sceneManager->Instantiate(entity);
	}

	{
		Entity* entity = new Entity();
		entity->objectName = "terrain";
		Transform* transform = static_cast<Transform*>(componentFactory->createComponent("Transform"));
		transform->position.x = 0;
		transform->position.y = 0;
		MeshComponent* meshComponent = static_cast<MeshComponent*>(componentFactory->createComponent("Mesh"));
		meshComponent->meshName = "terrain";
		Mesh* mesh = static_cast<Mesh*>(ResourceEngine::Instance()->GetGameResource("Mesh", meshComponent->meshName));
		meshComponent->vao_id = mesh->vao_id;
		meshComponent->numIndices = mesh->indices.size();
		entity->AddComponent(transform);
		entity->AddComponent(meshComponent);
		sceneManager->Instantiate(entity);
	}

	{
		Entity* entity = new Entity();
		entity->objectName = "ball1";
		Transform* transform = static_cast<Transform*>(componentFactory->createComponent("Transform"));
		transform->position.x = 0;
		transform->position.y = 0;
		MeshComponent* meshComponent = static_cast<MeshComponent*>(componentFactory->createComponent("Mesh"));
		meshComponent->meshName = "ball";
		Mesh* mesh = static_cast<Mesh*>(ResourceEngine::Instance()->GetGameResource("Mesh", meshComponent->meshName));
		meshComponent->colour = glm::vec3(0.0f, 0.0f, 1.0f);
		meshComponent->vao_id = mesh->vao_id;
		meshComponent->numIndices = mesh->indices.size();
		Velocity* velocity = new Velocity();
		velocity->currentVelocity = glm::vec3(5.0f, 13.0f, 0.0f);
		Acceleration* acceleration = new Acceleration();
		acceleration->currentAcceleration = glm::vec3(0.0f, -5.0f, 0.0f);
		SphereCollider* collider = new SphereCollider();
		entity->AddComponent(collider);
		entity->AddComponent(acceleration);
		entity->AddComponent(velocity);
		entity->AddComponent(transform);
		entity->AddComponent(meshComponent);
		sceneManager->Instantiate(entity);
	}

	{
		Entity* entity = new Entity();
		entity->objectName = "ball2";
		Transform* transform = static_cast<Transform*>(componentFactory->createComponent("Transform"));
		transform->position.x = -1;
		transform->position.y = -1;
		MeshComponent* meshComponent = static_cast<MeshComponent*>(componentFactory->createComponent("Mesh"));
		meshComponent->meshName = "ball";
		Mesh* mesh = static_cast<Mesh*>(ResourceEngine::Instance()->GetGameResource("Mesh", meshComponent->meshName));
		meshComponent->vao_id = mesh->vao_id;
		meshComponent->colour = glm::vec3(0.0f, 0.0f, 1.0f);
		meshComponent->numIndices = mesh->indices.size();
		Velocity* velocity = new Velocity();
		velocity->currentVelocity = glm::vec3(5.0f, 15.0f, 0.0f);
		Acceleration* acceleration = new Acceleration();
		acceleration->currentAcceleration = glm::vec3(0.0f, -5.0f, 0.0f);
		SphereCollider* collider = new SphereCollider();
		entity->AddComponent(collider);
		entity->AddComponent(acceleration);
		entity->AddComponent(velocity);
		entity->AddComponent(transform);
		entity->AddComponent(meshComponent);
		sceneManager->Instantiate(entity);
	}

	{
		Entity* entity = new Entity();
		entity->objectName = "ball3";
		Transform* transform = static_cast<Transform*>(componentFactory->createComponent("Transform"));
		transform->position.x = 0.2f;
		transform->position.y = 0.2f;
		transform->position.z = -5.2f;
		transform->scale.x = 3;
		transform->scale.y = 3;
		transform->scale.z = 3;
		MeshComponent* meshComponent = static_cast<MeshComponent*>(componentFactory->createComponent("Mesh"));
		meshComponent->meshName = "ball";
		Mesh* mesh = static_cast<Mesh*>(ResourceEngine::Instance()->GetGameResource("Mesh", meshComponent->meshName));
		meshComponent->vao_id = mesh->vao_id;
		meshComponent->colour = glm::vec3(0.0f, 0.0f, 1.0f);
		meshComponent->numIndices = mesh->indices.size();
		Velocity* velocity = new Velocity();
		velocity->currentVelocity = glm::vec3(5.0f, 20.0f, 0.0f);
		Acceleration* acceleration = new Acceleration();
		acceleration->currentAcceleration = glm::vec3(0.0f, -5.0f, 0.0f);
		SphereCollider* collider = new SphereCollider();
		entity->AddComponent(collider);
		entity->AddComponent(acceleration);
		entity->AddComponent(velocity);
		entity->AddComponent(transform);
		entity->AddComponent(meshComponent);
		sceneManager->Instantiate(entity);
	}

}
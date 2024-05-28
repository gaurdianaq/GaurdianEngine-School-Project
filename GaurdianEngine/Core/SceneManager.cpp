#include "SceneManager.h"
#include <iostream>
#include "../ResourceManager/ResourceManager.h"
#include "../ResourceManager/ResourceFactory.h"

SceneManager* SceneManager::instance;

SceneManager::SceneManager()
{
	activeScene = new Scene("defaultScene");
}

SceneManager* SceneManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::SaveScene(const char* filePath)
{
	serializer.SerializeJson(activeScene);
	serializer.WriteJsonToFile(filePath);
}

void SceneManager::SaveScene()
{
	serializer.SerializeJson(activeScene);
	serializer.WriteJsonToFile(activeScene->fileName);
}

glm::vec3 SceneManager::GetSceneColour()
{
	return activeScene->backgroundColour;
}

void SceneManager::LoadScene(const char* filePath)
{
	deserializer.DeserializeJson(filePath, activeScene);
	activeScene->fileName = filePath;
}

//Creates a new resource and adds it to the scene
void SceneManager::AddResourceToScene(std::string resourceType, std::string resourceName, std::string resourceFilePath)
{
	Resource* resource = resourceFactory->CreateResource(resourceType, resourceName, resourceFilePath);
	activeScene->pSceneResources[*resource->resourceType][resource->friendlyName];
}

//Adds an existing resource to the scene
void SceneManager::AddResourceToScene(Resource* resource)
{
	activeScene->pSceneResources[*resource->resourceType][resource->friendlyName] = resource;
}

std::unordered_map<std::string, Resource*> SceneManager::GetResourcesByType(std::string resourceType)
{
	return activeScene->pSceneResources[resourceType];
}

void SceneManager::Instantiate(Entity* entity)
{
	activeScene->pEntitiesByName[entity->objectName] = entity;
	for (std::unordered_map<std::string, Component*>::iterator it = entity->pComponents.begin(); it != entity->pComponents.end(); ++it)
	{
		activeScene->pEntitiesByComponent[it->first].push_back(entity);
	}
}

void SceneManager::Destroy(Entity* entity)
{
	for (std::unordered_map<std::string, Component*>::iterator it = entity->pComponents.begin(); it != entity->pComponents.end(); ++it)
	{
		for (int i = 0; i < activeScene->pEntitiesByComponent[it->first].size(); ++i)
		{
			if (activeScene->pEntitiesByComponent[it->first][i] == entity)
			{
				activeScene->pEntitiesByComponent[it->first].erase(activeScene->pEntitiesByComponent[it->first].begin()+i);
			}
		}

	}
	activeScene->pEntitiesByName.erase(entity->objectName);
	delete entity;
}

Entity* SceneManager::GetEntityByName(std::string entityName)
{
	return activeScene->pEntitiesByName[entityName];
}

Resource* SceneManager::GetResource(std::string resourceType, std::string resourceName)
{
	return activeScene->pSceneResources[resourceType][resourceName];
}

void SceneManager::SetActiveCamera(Entity* entity)
{
	activeScene->mainCamera = entity; //no checks done because I'll be nuking this soon (I Don't remember what I was planning on replacing this with...)
}

int SceneManager::GetSkyBox()
{
	return activeScene->skyBoxID;
}

Entity* SceneManager::GetActiveCamera()
{
	return activeScene->mainCamera;
}

std::vector<Entity*>* SceneManager::GetEntityByComponent(std::string componentType)
{
	return &activeScene->pEntitiesByComponent[componentType];
}
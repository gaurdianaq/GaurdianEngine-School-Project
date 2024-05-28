#include "Scene.h"
#include <rapidjson/document.h>
#include "../ResourceManager/ShaderManager/ShaderManager.h"
#include "../ResourceManager/MeshManager/MeshManager.h"
#include "../ResourceManager/AudioManager/AudioManager.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Core/SceneManager.h"
#include "../ResourceManager/ResourceFactory.h"
#include "../ResourceManager/TextureManager/Texture.h"

Scene::Scene(std::string _sceneName)
{
	sceneName = _sceneName;
}

void Scene::AddResourceToScene(Resource* resource)
{
	pSceneResources[*resource->resourceType][resource->friendlyName] = resource;
}

void Scene::Instantiate(Entity* entity)
{
	pEntitiesByName[entity->objectName] = entity;
	for (std::unordered_map<std::string, Component*>::iterator it = entity->pComponents.begin(); it != entity->pComponents.end(); ++it)
	{
		pEntitiesByComponent[it->first].push_back(entity);
	}
}


void Scene::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->Key("sceneName");
	writer->String(sceneName.c_str());
	writer->Key("backgroundColour");
	writer->StartObject();
	writer->Key("r");
	writer->Double(backgroundColour.r);
	writer->Key("g");
	writer->Double(backgroundColour.g);
	writer->Key("b");
	writer->Double(backgroundColour.b);
	writer->EndObject();
	writer->Key("Resources");
	writer->StartArray();
	for (std::unordered_map<std::string, std::unordered_map<std::string, Resource*>>::iterator it = pSceneResources.begin(); it != pSceneResources.end(); ++it)
	{
		writer->StartObject();
		writer->Key("ResourceType");
		writer->String(it->first.c_str());
		writer->Key("Resources");
		writer->StartArray();
		for (std::unordered_map<std::string, Resource*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			it2->second->Serialize(writer);
		}
		writer->EndArray();
		writer->EndObject();
	}
	writer->EndArray();
	writer->Key("Entities");
	writer->StartArray();
	for (std::unordered_map<std::string, Entity*>::iterator it = pEntitiesByName.begin(); it != pEntitiesByName.end(); ++it)
	{
		it->second->Serialize(writer);
	}
	writer->EndArray();
}

void Scene::Deserialize(Document& document)
{
	Resource* resource;
	Entity* entity;

	sceneName = document["sceneName"].GetString();
	backgroundColour.r = document["backgroundColour"]["r"].GetDouble();
	backgroundColour.g = document["backgroundColour"]["g"].GetDouble();
	backgroundColour.b = document["backgroundColour"]["b"].GetDouble();
	const Value& resourceMap = document["Resources"];
	const Value& entities = document["Entities"];
	std::string resourceTypeStr;
	for (Value::ConstValueIterator it = resourceMap.Begin(); it != resourceMap.End(); ++it)
	{
		const Value& resourceType = (*it)["ResourceType"];
		
		const Value& resources = (*it)["Resources"];
		for (Value::ConstValueIterator it2 = resources.Begin(); it2 != resources.End(); ++it2)
		{
			resourceTypeStr = ((*it)["ResourceType"].GetString());
			resource = resourceFactory->CreateResource((*it)["ResourceType"].GetString());
			resource->Deserialize(*it2);
			AddResourceToScene(resource);
		}
	}

	//load textures
	{
		std::unordered_map<std::string, Resource*> textures = sceneManager->GetResourcesByType("Texture");
		for (std::unordered_map<std::string, Resource*>::iterator it = textures.begin(); it != textures.end(); ++it)
		{
			resourceManager->LoadResource(it->second);
		}
	}


	skyBoxID = static_cast<Texture*>(resourceManager->GetResource("Texture", "skyBox"))->imageID; //currently no checks to make sure this is actually a cubemap, just ensuring it is myself

	//load meshes
	{
		std::unordered_map<std::string, Resource*> meshes = sceneManager->GetResourcesByType("Mesh");
		for (std::unordered_map<std::string, Resource*>::iterator it = meshes.begin(); it != meshes.end(); ++it)
		{
			resourceManager->LoadResource(it->second);
		}
	}

	//load audio (will eventually make it so it just loads all resource after shaders are loaded, or make shaders a seperate json
	{
		std::unordered_map<std::string, Resource*> sounds = sceneManager->GetResourcesByType("Audio");
		for (std::unordered_map<std::string, Resource*>::iterator it = sounds.begin(); it != sounds.end(); ++it)
		{
			resourceManager->LoadResource(it->second);
		}
	}

	//loads all entities into scene
	for (Value::ConstValueIterator it = entities.Begin(); it != entities.End(); ++it)
	{
		const Value& entityData = *it;
		entity = new Entity();
		entity->Deserialize(entityData);
		Instantiate(entity);
	}

}
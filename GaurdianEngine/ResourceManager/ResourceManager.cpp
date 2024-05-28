#include "ResourceManager.h"
#include "MeshManager/Mesh.h"
#include "ShaderManager/Shader.h"
#include "AudioManager/Audio.h"
#include "MeshManager/MeshManager.h"
#include "ShaderManager/ShaderManager.h"
#include "AudioManager/AudioManager.h"
#include "TextureManager/TextureManager.h"

ResourceManager* ResourceManager::instance;

ResourceManager::ResourceManager()
{

}

ResourceManager* ResourceManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::Start()
{
	resourceManagers["Shader"] = shaderManager;
	resourceManagers["Mesh"] = meshManager;
	resourceManagers["Texture"] = textureManager;
	resourceManagers["Audio"] = audioManager;
	//AudioManager::Instance()->Start();
}

bool ResourceManager::LoadResource(Resource* resource)
{
	if (resourceManagers[*resource->resourceType] != nullptr)
	{
		resourceManagers[*resource->resourceType]->LoadResource(resource);
		return true;
	}

	std::cout << resource->resourceType << " is not a recognized resource type!" << std::endl;
	return false;
}

Resource* ResourceManager::GetResource(std::string resourceType, std::string resourceName)
{
	if (resourceManagers[resourceType] != nullptr)
	{
		return resourceManagers[resourceType]->GetResource(resourceName);
	}

	std::cout << "No resource of that type found, returning nullptr" << std::endl;
	return nullptr;
}

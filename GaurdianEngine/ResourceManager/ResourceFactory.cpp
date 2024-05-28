#include "ResourceFactory.h"
#include "../Headers/ResourceTypes.h"
#include <iostream>

ResourceFactory* ResourceFactory::instance;

ResourceFactory* ResourceFactory::Instance()
{
	if (instance == nullptr)
	{
		instance = new ResourceFactory();
	}
	return instance;
}

ResourceFactory::ResourceFactory()
{

}

Resource* ResourceFactory::CreateResource(std::string resourceType, std::string resourceName, std::string resourceFilePath)
{
	if (resourceType == "Mesh")
	{
		return new Mesh(resourceFilePath, resourceName);
	}
	else if (resourceType == "Vertex_Shader")
	{
		return new Shader(VERTEX_SHADER, resourceFilePath, resourceName);
	}
	else if (resourceType == "Fragment_Shader")
	{
		return new Shader(FRAGMENT_SHADER, resourceFilePath, resourceName);
	}
	std::cout << resourceType.c_str() << " is not a valid resource type." << std::endl;
	return nullptr;
}

//factory that creates completely emplty resources, calling a default constructor
//should only be called by deserializer
Resource* ResourceFactory::CreateResource(std::string resourceType)
{
	if (resourceType == "Mesh")
	{
		return new Mesh();
	}
	else if (resourceType == "Shader")
	{
		return new Shader();
	}
	else if (resourceType == "Audio")
	{
		return new Audio();
	}
	else if (resourceType == "Texture")
	{
		return new Texture();
	}
	return nullptr;
}
#include "iResourceManager.h"

iResourceManager::iResourceManager()
{

}

iResourceManager::~iResourceManager()
{
	//resource cleanup
	for (std::unordered_map<std::string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it)
	{
		delete it->second;
	}
}

//interface to return a resource of a given name
Resource* iResourceManager::GetResource(std::string ResourceName)
{
	return resources[ResourceName];
}
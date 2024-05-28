#ifndef _RESOURCE_MANAGER_HG
#define _RESOURCE_MANAGER_HG

#include "iResourceManager.h"
#include <unordered_map>
#include <iostream>

//A unified interface for accessing different resource types
class ResourceManager
{
public:
	void Start();
	//void Stop();
	bool LoadResource(Resource* resource);
	Resource* GetResource(std::string resourceType, std::string resourceName);
	static ResourceManager* Instance();
private:
	ResourceManager();
	static ResourceManager* instance;
	std::unordered_map<std::string, iResourceManager*> resourceManagers;
};

#define resourceManager ResourceManager::Instance()

#endif // !_RESOURCE_MANAGER_HG

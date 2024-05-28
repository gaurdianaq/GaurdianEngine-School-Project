#ifndef _I_RESOURCE_MANAGER_HG
#define _I_RESOURCE_MANAGER_HG

#include "Resource.h"
#include <unordered_map>

//interface for resource managers (for loading and retrieving resources with a general interface)
class iResourceManager
{
public:
	iResourceManager();
	~iResourceManager();
	virtual void Init() = 0;
	virtual bool LoadResource(Resource* resource) = 0;
	Resource* GetResource(std::string resourceName);
protected:
	std::unordered_map<std::string, Resource*> resources;
};

#endif
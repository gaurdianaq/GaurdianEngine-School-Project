#ifndef _RESOURCE_FACTORY_HG
#define _RESOURCE_FACTORY_HG

#include "Resource.h"

class ResourceFactory
{
public:
	Resource* CreateResource(std::string resourceType, std::string resourceName, std::string resourceFilePath);
	Resource* CreateResource(std::string resourceType);
	static ResourceFactory* Instance();
private:
	ResourceFactory();
	static ResourceFactory* instance;
};

#define resourceFactory ResourceFactory::Instance()

#endif // !_RESOURCE_FACTORY_HG
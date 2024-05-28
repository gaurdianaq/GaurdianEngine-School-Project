#ifndef _COMPONENT_FACTORY_HG
#define _COMPONENT_FACTORY_HG

#include "Component.h"

//used to create any kind of component you could possibly need
class ComponentFactory
{
public:
	static ComponentFactory* Instance();
	Component* createComponent(std::string componentType);
private:
	ComponentFactory();
	static ComponentFactory* instance;
};

#define componentFactory ComponentFactory::Instance()

#endif
#ifndef _ENTITY_HG
#define _ENTITY_HG

#include <unordered_map>
#include "Component.h"

//represents any possible gameobject, is the basic building block of everything in a game
//can contain any number of components
class Entity : public ISerializeable, public IChildDeserializeable
{
public:
	Entity();
	std::string objectName;

	std::unordered_map<std::string, Component*> pComponents;
	bool isActive;

	void AddComponent(Component* component);
	Component* GetComponent(std::string componentType);

protected:
	friend class Scene;
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
};

#endif // !_ENTITY_HG

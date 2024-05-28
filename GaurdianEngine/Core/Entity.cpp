#include "Entity.h"
#include <iostream>
#include "ComponentFactory.h"

Entity::Entity()
{
	isActive = true;
}

Component* Entity::GetComponent(std::string componentType)
{
	return (pComponents[componentType]);
}

void Entity::AddComponent(Component* component)
{
	if (pComponents[*component->componentType] == nullptr)
	{
		pComponents[*component->componentType] = component;
	}
	else
	{
		std::cout << "Component of type: " << component->componentType << " already found in the map." << std::endl;
	}
}

void Entity::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("objectName");
	writer->String(objectName.c_str());
	writer->Key("isActive");
	writer->Bool(isActive);
	writer->Key("Components");
	writer->StartArray();
	for (std::unordered_map<std::string, Component*>::iterator it = pComponents.begin(); it != pComponents.end(); ++it)
	{
		writer->StartObject();
		writer->Key("ComponentType");
		writer->String(it->first.c_str());
		writer->Key(it->first.c_str());
		it->second->Serialize(writer);
		writer->EndObject();
	}
	writer->EndArray();
	writer->EndObject();
}

void Entity::Deserialize(const Value& value)
{
	const Value& components = value["Components"];
	std::string componentType;
	objectName = value["objectName"].GetString();
	isActive = value["isActive"].GetBool();

	for (Value::ConstValueIterator it = components.Begin(); it != components.End(); ++it)
	{
		componentType = ((*it)["ComponentType"].GetString());
		Component* component = componentFactory->createComponent(componentType);
		component->Deserialize((*it)[componentType.c_str()]);
		AddComponent(component);
	}
	
}
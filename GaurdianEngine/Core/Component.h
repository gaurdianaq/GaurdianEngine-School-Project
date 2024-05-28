#ifndef _COMPONENT_HG
#define _COMPONENT_HG

#include "../Serialization/ISerializeable.h"
#include <string>

//base class for components, the building blocks of any entity
class Component : public ISerializeable, public IChildDeserializeable
{
public:
	const std::string* componentType;
	bool isActive = true;
	virtual ~Component() = 0;
protected:
	friend class Entity;
	void Serialize(PrettyWriter<StringBuffer>* writer) = 0;
	void Deserialize(const Value& value) = 0;
	const static std::string _componentType;
};

#endif // !_COMPONENT_HG

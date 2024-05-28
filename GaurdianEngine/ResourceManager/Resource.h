#ifndef _RESOURCE_HG
#define _RESOURCE_HG

#include <string>
#include "../Serialization/ISerializeable.h"

class Resource : public ISerializeable, public IChildDeserializeable
{
public:
	Resource();
	~Resource();
	std::string filePath;
	std::string friendlyName;
	const std::string* resourceType;
protected:
	friend class Scene;
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _resourceType;
};

#endif // !_RESOURCE_HG

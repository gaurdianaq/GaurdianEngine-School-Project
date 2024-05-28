#ifndef _SERIALIZEABLE_HG
#define _SERIALIZEABLE_HG

#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>

using namespace rapidjson;

//Represents an object that can be serialized;
class ISerializeable
{
	friend class Serializer;
protected:
	virtual void Serialize(PrettyWriter<StringBuffer>* writer) = 0;
};

//represents an object that can be deserialized
class IDeserializeable
{
	friend class Deserializer;
protected:
	virtual void Deserialize(Document& document) = 0;
};

//represents of an object that is a child of a class that can be deserialized
class IChildDeserializeable
{
	friend class Deserializer;
protected:
	virtual void Deserialize(const Value& value) = 0;
};



#endif // !_SERIALIZEABLE_HG

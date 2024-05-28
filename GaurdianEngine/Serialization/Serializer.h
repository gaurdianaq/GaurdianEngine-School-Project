#ifndef _SERIALIZER_HG
#define _SERIALIZER_HG

#include "ISerializeable.h"
#include <string>

//Serializer lets you serialize any class that implements ISerializeable
class Serializer
{
public:
	Serializer();
	~Serializer();
	void SerializeJson(ISerializeable* serializeable);
	void WriteJsonToFile(std::string filePath);
private:
	StringBuffer sBuffer;
	PrettyWriter<StringBuffer>* writer;
};

//Deserializer lets you deserialize any class that implements IDeserializeable
class Deserializer
{
public:
	Deserializer();
	~Deserializer();
	void DeserializeJson(const char* filePath, IDeserializeable* serializeable);
private:
	Document document;
};

#endif // !_SERIALIZER_HG



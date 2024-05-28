#include "Resource.h"

const std::string Resource::_resourceType = "Resource";

Resource::Resource()
{
	resourceType = &_resourceType;
}

Resource::~Resource()
{

}

void Resource::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("friendlyName");
	writer->String(friendlyName.c_str());
	writer->Key("filePath");
	writer->String(filePath.c_str());
	writer->EndObject();
}

void Resource::Deserialize(const Value& value)
{
	friendlyName = value["friendlyName"].GetString();
	filePath = value["filePath"].GetString();
}
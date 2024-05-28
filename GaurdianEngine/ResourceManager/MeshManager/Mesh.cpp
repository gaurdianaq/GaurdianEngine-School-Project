#include "Mesh.h"

const std::string Mesh::_resourceType = "Mesh";

Mesh::Mesh(std::string _filePath, std::string _friendlyName)
{
	resourceType = &_resourceType;
	filePath = _filePath;
	friendlyName = _friendlyName;
}

Mesh::Mesh()
{
	resourceType = &_resourceType;
}

void Mesh::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("friendlyName");
	writer->String(friendlyName.c_str());
	writer->Key("filePath");
	writer->String(filePath.c_str());
	writer->EndObject();
}

void Mesh::Deserialize(const Value& value)
{
	friendlyName = value["friendlyName"].GetString();
	filePath = "assets/meshes/" + (std::string)value["filePath"].GetString();
}
#include "Texture.h"
#include <soil/SOIL2.h>

const std::string Texture::_resourceType = "Texture";

std::string textureTypeToString(TextureType type)
{
	switch (type)
	{
	case TextureType::Normal:
		return "Normal";
		break;
	case TextureType::Cubemap:
		return "Cubemap";
		break;
	case TextureType::Unknown:
		return "Unknown type";
		break;
	default:
		return "You managed to break an enum, I hope you're proud...";
	}
}

TextureType stringToTextureType(std::string typeName)
{
	if (typeName == "Normal")
	{
		return TextureType::Normal;
	}
	else if (typeName == "CubeMap")
	{
		return TextureType::Cubemap;
	}
	return TextureType::Unknown;
}

Texture::Texture()
{
	resourceType = &_resourceType;
}

Texture::Texture(std::string _filePath, std::string _friendlyName, TextureType _type)
{
	filePath = _filePath;
	friendlyName = _friendlyName;
	type = _type;
	resourceType = &_resourceType;
}

void Texture::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("friendlyName");
	writer->String(friendlyName.c_str());
	writer->Key("filePath");
	writer->String(filePath.c_str());
	writer->Key("type");
	writer->String(textureTypeToString(type).c_str());
	writer->EndObject();
}

void Texture::Deserialize(const Value& value)
{
	friendlyName = value["friendlyName"].GetString();
	filePath = "assets/textures/" + (std::string)value["filePath"].GetString();
	type = stringToTextureType(value["type"].GetString());
}
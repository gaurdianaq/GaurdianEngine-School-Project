#ifndef _TEXTURE_HG
#define _TEXTURE_HG

#include "../Resource.h"

enum class TextureType { Normal, Cubemap, Unknown };

class Texture : public Resource
{
public:
	Texture();
	Texture(std::string _filePath, std::string _friendlyName, TextureType _type);
	unsigned int imageID;
	TextureType type;
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _resourceType;
};

#endif
#include "TextureManager.h"
#include <soil/SOIL2.h>

TextureManager* TextureManager::instance;

TextureManager::TextureManager()
{
	Init();
}

TextureManager::~TextureManager()
{
	
}

void TextureManager::Init()
{
	//here for interface (for now)
}

TextureManager* TextureManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}

bool TextureManager::LoadResource(Resource* resource)
{
	Texture* texture = static_cast<Texture*>(resource);
	if (texture->type == TextureType::Normal)
	{
		texture->imageID = SOIL_load_OGL_texture
		(
			texture->filePath.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS
		);
	}
	else if (texture->type == TextureType::Cubemap)
	{
		texture->imageID = SOIL_load_OGL_single_cubemap
		(
			texture->filePath.c_str(),
			"EWUDNS",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB
		);
	}
	
	if (texture->imageID == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else
	{
		resources[texture->friendlyName] = texture;
		return true;
	}

}

Resource* TextureManager::GetResource(std::string resourceName)
{
	return resources[resourceName];
}
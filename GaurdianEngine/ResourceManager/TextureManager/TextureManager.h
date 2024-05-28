#ifndef _TEXTURE_MANAGER_HG
#define _TEXTURE_MANAGER_HG

#include "Texture.h"
#include "../iResourceManager.h"

class TextureManager : public iResourceManager
{
public:
	static TextureManager* Instance();
	~TextureManager();
	void Init();
	bool LoadResource(Resource* resource);
	Resource* GetResource(std::string resourceName);
private:
	TextureManager();
	static TextureManager* instance;
};

#define textureManager TextureManager::Instance()

#endif
#ifndef _SHADER_MANAGER_HG
#define _SHADER_MANAGER_HG

#include "../iResourceManager.h"
#include "../../Serialization/Serializer.h"
#include <unordered_map>

class ShaderManager : public iResourceManager, IDeserializeable
{
public:
	static ShaderManager* Instance();
	~ShaderManager();
	void CreateShaderProgram();
	void Init();
	bool LoadResource(Resource* resource);
	bool compileShader(std::string shaderName);
	bool linkProgram();
	void getShaderCompileInfo(std::string shaderName);
	bool getShaderLinkInfo(unsigned int programID);
	int GetShaderProgram();
protected:
	void Deserialize(Document& document);
private:
	ShaderManager();
	Deserializer deserializer;
	static ShaderManager* instance;
	int program;
	//ShaderProgram program;
};

#define shaderManager ShaderManager::Instance()

#endif // !_SHADERMANAGER_HG

#ifndef _SHADER_HG
#define _SHADER_HG

#include <vector>
#include <glad/glad.h>
#include "../Resource.h"
#include "ShaderProgram.h"

enum eShaderType
{
	VERTEX_SHADER,
	TESSELATION_CONTROL_SHADER,
	TESSELATION_EVALUATION_SHADER,
	GEOMETRY_SHADER,
	FRAGMENT_SHADER,
	UNKNOWN
};

int getShaderInt(eShaderType type);
std::string getShaderTypeString(eShaderType type);

class Shader : public Resource
{
	friend class ShaderManager;
public:
	unsigned int id;
	eShaderType shaderType;
	std::vector<std::string> vecSource;
	unsigned int numLines;
	char** shaderContent;
	Shader(eShaderType type, std::string _filePath, std::string _friendlyName);
	Shader();
	int program; //reference to program that shader is attached to
protected:
	void Serialize(PrettyWriter<StringBuffer>* writer);
	void Deserialize(const Value& value);
	const static std::string _resourceType;
};

#endif // !_SHADER_HG

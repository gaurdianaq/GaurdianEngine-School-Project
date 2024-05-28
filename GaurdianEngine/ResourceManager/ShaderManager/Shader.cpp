#include "Shader.h"

const std::string Shader::_resourceType = "Shader";

Shader::Shader(eShaderType type, std::string _filePath, std::string _friendlyName)
{
	resourceType = &_resourceType;
	id = 0;
	shaderType = type;
	filePath = _filePath;
	friendlyName = _friendlyName;
}

Shader::Shader()
{
	resourceType = &_resourceType;
	id = 0;
}

//returns the int value used by opengl to represent a shader type
int getShaderInt(eShaderType type)
{
	switch (type)
	{
	case VERTEX_SHADER:
		return GL_VERTEX_SHADER;
		break;
	case TESSELATION_CONTROL_SHADER:
		return GL_TESS_CONTROL_SHADER;
		break;
	case TESSELATION_EVALUATION_SHADER:
		return GL_TESS_EVALUATION_SHADER;
		break;
	case GEOMETRY_SHADER:
		return GL_GEOMETRY_SHADER;
		break;
	case FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER;
		break;
	}
}

//takes shader type enum and outputs a string
std::string getShaderTypeString(eShaderType type)
{
	switch (type)
	{
	case VERTEX_SHADER:
		return "Vertex_Shader";
		break;
	case TESSELATION_CONTROL_SHADER:
		return "Tesselation_Control_Shader";
		break;
	case TESSELATION_EVALUATION_SHADER:
		return "Tesselation_Evaluation_Shader";
		break;
	case GEOMETRY_SHADER:
		return "Geometry_Shader";
		break;
	case FRAGMENT_SHADER:
		return "Fragment_Shader";
		break;
	case UNKNOWN:
	default:
		return "UNKNOWN_SHADER_TYPE";
		break;
	}
}

//takes a string and returns the appropriate enum for shadertype
eShaderType getShaderTypeByString(std::string type)
{
	if (type == "Vertex_Shader")
	{
		return VERTEX_SHADER;
	}
	else if (type == "Tesselation_Control_Shader")
	{
		return TESSELATION_CONTROL_SHADER;
	}
	else if (type == "Tesselation_Evaluation_Shader")
	{
		return TESSELATION_EVALUATION_SHADER;
	}
	else if (type == "Geometry_Shader")
	{
		return GEOMETRY_SHADER;
	}
	else if (type == "Fragment_Shader")
	{
		return FRAGMENT_SHADER;
	}
}

void Shader::Serialize(PrettyWriter<StringBuffer>* writer)
{
	writer->StartObject();
	writer->Key("friendlyName");
	writer->String(friendlyName.c_str());
	writer->Key("filePath");
	writer->String(filePath.c_str());
	writer->Key("shaderType");
	writer->String(getShaderTypeString(shaderType).c_str());
	writer->EndObject();
}

void Shader::Deserialize(const Value& value)
{
	friendlyName = value["friendlyName"].GetString();
	filePath = "assets/shaders/" + (std::string)value["filePath"].GetString();
	shaderType = getShaderTypeByString(value["shaderType"].GetString());
}
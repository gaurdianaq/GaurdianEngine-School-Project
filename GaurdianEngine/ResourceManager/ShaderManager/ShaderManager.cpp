#include "ShaderManager.h"
#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <glad/glad.h>	// For all the OpenGL calls, etc.

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager* ShaderManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new ShaderManager();
	}
	return instance;
}

ShaderManager::ShaderManager()
{
	Init();
}

ShaderManager::~ShaderManager()
{

}


void ShaderManager::CreateShaderProgram()
{
	program = glCreateProgram();
}


int getShaderBit(eShaderType type)
{
	switch (type)
	{
	case VERTEX_SHADER:
		return GL_VERTEX_SHADER_BIT;
		break;
	case TESSELATION_CONTROL_SHADER:
		return GL_TESS_CONTROL_SHADER_BIT;
		break;
	case TESSELATION_EVALUATION_SHADER:
		return GL_TESS_EVALUATION_SHADER_BIT;
		break;
	case GEOMETRY_SHADER:
		return GL_GEOMETRY_SHADER_BIT;
		break;
	case FRAGMENT_SHADER:
		return GL_FRAGMENT_SHADER_BIT;
		break;
	}
}

bool ShaderManager::LoadResource(Resource* resource)
{
	Shader* shader = static_cast<Shader*>(resource);
	shader->program = program;
	if (shader == nullptr)
	{
		std::cout << "Resource passed is not a shader!" << std::endl;
		return false;
	}
	std::ifstream shaderFile;
	std::string line;
	unsigned int counter = 0;

	shaderFile.open(shader->filePath, std::ios::in);
	if (shaderFile.is_open())
	{
		std::vector<std::string> lines;

		while (getline(shaderFile, line))
		{
			lines.push_back(line);
		}
		shader->numLines = lines.size();
		shaderFile.close();
		shader->shaderContent = new char*[lines.size()];
		//memset(shaders[type]->shaderContent, 0, lines.size());
		for (unsigned int i = 0; i < lines.size(); ++i)
		{
			shader->shaderContent[i] = new char[lines[i].size() + 2];
			//memset(shaders[type]->shaderContent[i], 0, lines[i].size() + 2);
			for (unsigned int n = 0; n < lines[i].size(); ++n)
			{
				shader->shaderContent[i][n] = lines[i][n];
			}
			shader->shaderContent[i][lines[i].size()] = '\n';
			shader->shaderContent[i][lines[i].size() + 1] = '\0';
		}
		resources[shader->friendlyName] = shader;
		std::cout << "Successfully read shader file and wrote the " << getShaderTypeString(shader->shaderType) << std::endl;
		compileShader(shader->friendlyName);
		return true;
	}
	else
	{
		std::cout << "Could not open shader file " << shader->filePath << std::endl;
		return false;
	}
}

bool ShaderManager::compileShader(std::string shaderName)
{
	
	Shader* shader = static_cast<Shader*>(resources[shaderName]);
	shader->id = glCreateShader(getShaderInt(shader->shaderType));
	glShaderSource(shader->id, shader->numLines, shader->shaderContent, nullptr);
	glCompileShader(shader->id);
	getShaderCompileInfo(shader->friendlyName);
	return true;
}

int ShaderManager::GetShaderProgram()
{
	return program;
}

bool ShaderManager::linkProgram()
{
	for (std::unordered_map<std::string, Resource*>::iterator it = resources.begin(); it != resources.end(); ++it)
	{
		Shader* shader = static_cast<Shader*>(resources[it->first]);
		glAttachShader(shader->program, shader->id);
	}
	glLinkProgram(program);
	if (!getShaderLinkInfo(program))
	{
		std::cout << "There was an error linking the program!" << std::endl;
		return false;
	}
	std::cout << "Programs successfully linked!" << std::endl;
	return true;
}

bool ShaderManager::getShaderLinkInfo(unsigned int programID)
{
	GLint wasError = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &wasError);
	GLint maxLength = 0;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

	char* pLogText = new char[maxLength];
	// Fill with zeros, maybe...?
	glGetProgramInfoLog(programID, maxLength, &maxLength, pLogText);
	std::cout << pLogText << std::endl;

	if (wasError == -1)
	{
		return false;
	}
	return true;
}

void ShaderManager::getShaderCompileInfo(std::string shaderName)
{
	Shader* shader = static_cast<Shader*>(resources[shaderName]);
	GLint isCompiled = 0;
	glGetShaderiv(shader->id, GL_COMPILE_STATUS, &isCompiled);
	GLint maxLength = 5;
	glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, &maxLength);

	char* pLogText = new char[maxLength];
	glGetShaderInfoLog(shader->id, maxLength, &maxLength, pLogText);
	std::cout << pLogText << std::endl;

	if (isCompiled == GL_FALSE)
	{
		std::cout << "Couldn't compile " << getShaderTypeString(shader->shaderType) << std::endl;
	}
	else if (isCompiled == GL_TRUE)
	{
		std::cout << getShaderTypeString(shader->shaderType) << " compiled successfully!" << std::endl;
	}
}

void ShaderManager::Init()
{
	CreateShaderProgram();
	deserializer.DeserializeJson("shaderconfig.json", this);
}

void ShaderManager::Deserialize(Document& document)
{
	for (Value::ConstValueIterator it = document["Shaders"].Begin(); it != document["Shaders"].End(); ++it)
	{
		Shader* shader = new Shader();
		shader->Deserialize(*it);
		LoadResource(shader);
	}

	linkProgram();
}
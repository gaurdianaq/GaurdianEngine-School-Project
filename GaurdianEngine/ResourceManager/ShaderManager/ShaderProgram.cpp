#include "ShaderProgram.h"
#include <glad/glad.h>

ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
}
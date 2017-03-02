#include "Shader.h"
#include <fstream>
#include "../debug/Debug.h"

void Shader::install()
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* shaderCode[1];

	std::string temp = readShadercode(vertexShader).c_str();
	shaderCode[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, shaderCode, nullptr);
	temp = readShadercode(fragmentShader).c_str();
	shaderCode[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, shaderCode, nullptr);

	glCompileShader(vertexShaderID);
	if (!checkShaderStatus(vertexShaderID))
	{
		Debug::print(shaderName);
		Debug::print("failed to compile vertex shader");
		return;
	}
	glCompileShader(fragmentShaderID);
	if (!checkShaderStatus(fragmentShaderID))
	{
		Debug::print(shaderName);
		Debug::print("failed to compile fragment shader");
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);

	if (!checkProgramStatus(programID))
	{
		Debug::print(shaderName);
		Debug::print("failed to link the program");
		return;
	}
}

void Shader::start()
{
	glUseProgram(programID);
}

void Shader::stop()
{
	glUseProgram(0);
}

void Shader::cleanUp()
{
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glDeleteProgram(programID);
}

std::string Shader::readShadercode(const std::string& file)
{
	std::ifstream input(file);
	if (!input.good())
	{
		Debug::print(shaderName);
		Debug::print(file);
		Debug::print("File failed to load");
	}
	return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}

bool Shader::checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetter, PFNGLGETSHADERINFOLOGPROC getInfoLogFun, GLenum statusType)
{
	GLint status;
	objectPropertyGetter(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetter(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		getInfoLogFun(objectID, infoLogLength, &bufferSize, buffer);

		Debug::print(buffer);

		delete[] buffer;
		return false;
	}
	return true;
}


bool Shader::checkShaderStatus(GLuint ShaderID)
{
	return checkStatus(ShaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool Shader::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	const GLchar* adapter[1];
	std::string temp = uniformName.c_str();
	adapter[0] = temp.c_str();
	return glGetUniformLocation(programID, adapter[0]);
}
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
		Debug::print(name);
		Debug::print("failed to compile vertex shader");
		Debug::print(" ");
		return;
	}
	glCompileShader(fragmentShaderID);
	if (!checkShaderStatus(fragmentShaderID))
	{
		Debug::print(name);
		Debug::print("failed to compile fragment shader");
		Debug::print(" ");
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);

	if (!checkProgramStatus(programID))
	{
		Debug::print(name);
		Debug::print("failed to link the program");
		Debug::print(" ");
		return;
	}
	getAllUniformLocations();
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
		Debug::print(name);
		Debug::print(file);
		Debug::print("File failed to load");
		Debug::print(" ");
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

void Shader::loadTransformationToUniform(std::shared_ptr<Entity> entity)
{
	loadToUniform(location_transformationMatrix, GLMath::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale()));
	loadToUniform(location_viewMatrix, viewMatrix);
	loadToUniform(location_projectionMatrix, projectionMatrix);
}

void Shader::getAllUniformLocations()
{
	std::string temp;

	temp = "transformationMatrix";
	location_transformationMatrix = getUniformLocation(temp);

	temp = "viewMatrix";
	location_viewMatrix = getUniformLocation(temp);

	temp = "projectionMatrix";
	location_projectionMatrix = getUniformLocation(temp);
}

GLint Shader::getUniformLocation(const std::string& uniformName)
{
	const GLchar* adapter[1];
	std::string temp = uniformName.c_str();
	adapter[0] = temp.c_str();
	return glGetUniformLocation(programID, adapter[0]);
}
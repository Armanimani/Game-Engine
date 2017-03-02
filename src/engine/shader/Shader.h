#pragma once

#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include "../model/Model.h"
#include <memory>
#include "ShaderType.h"

class Shader
{
public:
	Shader() {};
	Shader(const std::string& vertexShader, const std::string& fragmentShader) : vertexShader(vertexShader), fragmentShader(fragmentShader) {}
	void install();
	void start();
	void stop();
	void cleanUp();

	virtual void render(const std::shared_ptr<Model> model) = 0;
	
	inline const std::string& getName() { return shaderName; }
	inline const ShaderType& getType() { return shaderType; }

protected:
	ShaderType shaderType;
	std::string shaderName;
	std::string vertexShader;
	std::string fragmentShader;

	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	std::string readShadercode(const std::string& file);
	bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetter, PFNGLGETSHADERINFOLOGPROC getInfoLogFun, GLenum statusType);
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint programID);

	virtual void getAllUniformLocations() {};
	GLint getUniformLocation(const std::string& uniformName);

	inline void loadToUniform(GLuint &location, GLboolean &data) { glUniform1f(location, data); }
	inline void loadToUniform(GLuint &location, GLfloat &data) { glUniform1f(location, data); }
	inline void loadToUniform(GLuint &location, glm::vec2 &data) { glUniform2fv(location, 1, &data[0]); }
	inline void loadToUniform(GLuint &location, glm::vec3 &data) { glUniform3fv(location, 1, &data[0]); }
	inline void loadToUniform(GLuint &location, glm::vec4 &data) { glUniform3fv(location, 1, &data[0]); }
	inline void loadToUniform(GLuint &location, glm::mat3 &data) { glUniformMatrix3fv(location, 1, GL_FALSE, &data[0][0]); }
	inline void loadToUniform(GLuint &location, glm::mat4 &data) { glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]); }
};
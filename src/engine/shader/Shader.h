#pragma once

#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <string>

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexShader, const std::string& fragmentShader) : vertexShader(vertexShader), fragmentShader(fragmentShader) {}
	void install() {};
	void start() {};
	void stop() {};
	void cleanUp() {};

protected:
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	std::string vertexShader;
	std::string fragmentShader;

	inline void loadToUniform(GLuint &location, GLboolean &data) { glUniform1f(location, data); }
	inline void loadToUniform(GLuint &location, GLfloat &data) { glUniform1f(location, data); }
	inline void loadToUniform(GLuint &location, glm::vec2 &data) { glUniform2fv(location, 1, &data[0]); }
	inline void loadToUniform(GLuint &location, glm::vec3 &data) { glUniform3fv(location, 1, &data[0]); }
	inline void loadToUniform(GLuint &location, glm::vec4 &data) { glUniform3fv(location, 1, &data[0]); }
	inline void loadToUniform(GLuint &location, glm::mat3 &data) { glUniformMatrix3fv(location, 1, GL_FALSE, &data[0][0]); }
	inline void loadToUniform(GLuint &location, glm::mat4 &data) { glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]); }
};
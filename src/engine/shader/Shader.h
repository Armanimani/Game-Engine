#pragma once

#include <glew\GL\glew.h>
#include <glm\glm.hpp>
#include <string>
#include "../model/Model.h"
#include <memory>
#include "ShaderType.h"
#include "../mesh/Mesh.h"
#include "../entity/Entity.h"
#include "../math/GLMath.h"

class Shader
{
public:
	Shader() {};
	Shader(const std::string& name, const ShaderType& type, const std::string& vertexShader, const std::string& fragmentShader) : name(name), type(type), vertexShader(vertexShader), fragmentShader(fragmentShader) {}
	void install();
	void start();
	void stop();
	void cleanUp();

	virtual void render(const std::shared_ptr<Entity> entity) = 0;
	
	inline const std::string& getName() { return name; }
	inline const ShaderType& getType() { return type; }

protected:
	ShaderType type;
	std::string name;

	std::string vertexShader;
	std::string fragmentShader;

	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmentShaderID;

	GLuint location_transformationMatrix;

	std::string readShadercode(const std::string& file);
	bool checkStatus(GLuint objectID, PFNGLGETSHADERIVPROC objectPropertyGetter, PFNGLGETSHADERINFOLOGPROC getInfoLogFun, GLenum statusType);
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint programID);

	virtual void getAllUniformLocations();
	GLint getUniformLocation(const std::string& uniformName);

	inline void loadToUniform(const GLuint &location, const GLboolean &data) { glUniform1f(location, data); }
	inline void loadToUniform(const GLuint &location, const GLfloat &data) { glUniform1f(location, data); }
	inline void loadToUniform(const GLuint &location, const glm::vec2 &data) { glUniform2fv(location, 1, &data[0]); }
	inline void loadToUniform(const GLuint &location, const glm::vec3 &data) { glUniform3fv(location, 1, &data[0]); }
	inline void loadToUniform(const GLuint &location, const glm::vec4 &data) { glUniform3fv(location, 1, &data[0]); }
	inline void loadToUniform(const GLuint &location, const glm::mat3 &data) { glUniformMatrix3fv(location, 1, GL_FALSE, &data[0][0]); }
	inline void loadToUniform(const GLuint &location, const glm::mat4 &data) { glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]); }
};
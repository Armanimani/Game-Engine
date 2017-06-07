#pragma once
#include <string>
#include <glew\GL\glew.h>
#include "glm\glm.hpp"

class Fog
{
public:
	Fog(const std::string& name, const glm::vec4& color, const GLfloat& density) : name(name), color(color), density(density) {}

	inline void setName(const std::string& value) { name = value; }
	inline const std::string& getName() { return name; }

	inline void setColor(const glm::vec4& value) { color = value; }
	inline const glm::vec4& getColor() { return color; }

	inline void setDensity(const GLfloat& value) { density = value; }
	inline const GLfloat& getDensity() { return density; }

protected:
	std::string name;
	glm::vec4 color;
	GLfloat density;
};
#pragma once
#include "LightType.h"
#include "glew\GL\glew.h"
#include <glm\glm.hpp>
#include <string>

class Light
{
public:
	Light(const std::string& name, const glm::vec3& position, const glm::vec3& color, const GLfloat& ambientIntensity = 0.0, const GLfloat& diffuseIntensity = 0.0, const GLfloat& specularIntensity = 0.0, const GLboolean& shadow = false) : name(name), position(position), color(color), diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity), shadow(shadow){}
	
	inline void setName(const std::string& value) { name = value; }
	inline const std::string& getName() { return name; }

	inline void setType(const LightType& value) { type = value; }
	inline const LightType& getType() { return type; }

	inline void setPosition(const glm::vec3& value) { position = value; }
	inline const glm::vec3& getPosition() { return position; }

	inline void setColor(const glm::vec3& value) { color = value; }
	inline const glm::vec3& getColor() { return color; }

	inline void setDiffuseIntensity(const GLfloat& value) 
	{
		if (value > 1.0) diffuseIntensity = 1.0;
		else if (value < 0.0) diffuseIntensity = 0.0;
		else diffuseIntensity = value;
	}
	inline const GLfloat& getDiffuseIntensity() { return diffuseIntensity; }

	inline void setSpecularIntensity(const GLfloat& value)
	{
		if (value > 1.0) specularIntensity = 1.0;
		else if (value < 0.0) specularIntensity = 0.0;
		else specularIntensity = value;
	}

	inline const GLfloat& getSpecularIntensity() { return specularIntensity; }

	inline void setShadow(const GLboolean& state = true) { shadow = state; }
	inline const GLboolean& getShadow() { return shadow; }

	inline void setOn(const GLboolean& state = true) { on = state; }
	inline const GLboolean& getOn() { return on; }

protected:
	std::string name;
	LightType type = LightType::noType;
	glm::vec3 position;
	glm::vec3 color;
	GLfloat diffuseIntensity;
	GLfloat specularIntensity;
	GLboolean on = true;
	GLboolean shadow = false;
};
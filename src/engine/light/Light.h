#pragma once
#include "LightType.h"
#include "glew\GL\glew.h"
#include <glm\glm.hpp>
#include <string>

class Light
{
public:
	Light(const std::string& name, const glm::vec3& position, const GLfloat& attenuationFactor, const LightType& type = LightType::noType) : name(name), position(position), type(type), attenuationFactor(attenuationFactor){}
	
	inline void setName(const std::string& value) { name = value; }
	inline const std::string& getName() { return name; }

	inline void setType(const LightType& value) { type = value; }
	inline const LightType& getType() { return type; }

	inline void setPosition(const glm::vec3& value) { position = value; }
	inline const glm::vec3& getPosition() { return position; }

	inline void setAttenuationFactor(const GLfloat& factor) { attenuationFactor = factor; }
	inline const GLfloat& getAttenuationFactor() { return attenuationFactor; }

	inline void setOn(const GLboolean& state = true) { on = state; }
	inline const GLboolean& getOn() { return on; }

protected:
	std::string name;
	LightType type;
	glm::vec3 position;
	GLfloat attenuationFactor = 0.0;
	GLboolean on = true;
	
};
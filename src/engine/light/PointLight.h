#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(const std::string& name, const glm::vec3& position, const glm::vec4& diffuseColor, const glm::vec4& specularColor, const GLfloat& diffuseIntensity, const GLfloat& specularIntensity, const GLfloat& attenuationFactor, const GLboolean& shadow) : Light(name, position, attenuationFactor, LightType::point), diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity), shadow(shadow), diffuseColor(diffuseColor), specularColor(specularColor) {}

	inline void setDiffuseColor(const glm::vec4& color) { diffuseColor = color; }
	inline const glm::vec4& getDiffuseColor() { return diffuseColor; }

	inline void setSpecularColor(const glm::vec4& color) { specularColor = color; }
	inline const glm::vec4& getSpecularColor() { return specularColor; }

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
protected:
	GLfloat diffuseIntensity;
	GLfloat specularIntensity;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	GLboolean shadow = false;
};
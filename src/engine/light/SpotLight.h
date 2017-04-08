#pragma once

#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(const std::string& name, const glm::vec3& position, const glm::vec3& direction, const glm::vec4& diffuseColor, const glm::vec4& specularColor, const GLfloat& diffuseIntensity, const GLfloat& specularIntensity, const GLfloat& attenuationFactor, const GLfloat& exponent, const GLfloat& cutoff, const GLboolean& shadow) : Light(name, position, attenuationFactor, LightType::spot), diffuseIntensity(diffuseIntensity), specularIntensity(specularIntensity), shadow(shadow), diffuseColor(diffuseColor), specularColor(specularColor), exponent(exponent), cutoff(cutoff), direction(glm::normalize(direction)) {}

	inline void setDirection(const glm::vec3& value) { direction = value; }
	inline const glm::vec3& getDirection() { return direction; }

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

	inline const GLfloat& getExponent() { return exponent; }
	inline void setExponent(const GLfloat& value) { exponent = value; }

	inline const GLfloat& getCutoff() { return cutoff; }
	inline void setCutoff(const GLfloat& value) { cutoff = value; }

	inline void setShadow(const GLboolean& state = true) { shadow = state; }
	inline const GLboolean& getShadow() { return shadow; }

protected:
	glm::vec3 direction;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	GLfloat diffuseIntensity;
	GLfloat specularIntensity;
	GLfloat exponent;
	GLfloat cutoff;
	GLboolean shadow = false;
};
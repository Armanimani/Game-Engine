#pragma once
#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight(const std::string& name, const glm::vec3& position, const glm::vec3& color, const GLfloat& ambientIntensity = 0.0) : Light(name, position, color, ambientIntensity, 0.0f, 0.0f, false) 
	{ 
		type = LightType::ambient;
		this->ambientIntensity = ambientIntensity;
	}

	inline void setDiffuseIntensity(const GLfloat& value) = delete;
	inline const GLfloat& getDiffuseIntensity() = delete;
	inline void setSpecularIntensity(const GLfloat& value) = delete;
	inline const GLfloat& getSpecularIntensity() = delete;
	inline void setShadow(const GLboolean& state = true) = delete;
	inline const GLboolean& getShadow() = delete;

	inline void setAmbientIntensity(const GLfloat& value)
	{
		if (value > 1.0) ambientIntensity = 1.0;
		else if (value < 0.0) ambientIntensity = 0.0;
		else ambientIntensity = value;
	}
	inline const GLfloat& getAmbientIntensity() { return ambientIntensity; }

protected:
	GLfloat ambientIntensity;

};
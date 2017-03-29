#pragma once
#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight(const std::string& name, const glm::vec3& position, const GLfloat& intensity, const glm::vec4& color, const GLfloat& attenuationFactor ) : Light(name, position, attenuationFactor, LightType::ambient), intensity(intensity), color(color) {}

	inline void setColor(const glm::vec4& value) { color = value; }
	inline const glm::vec4& getColor() { return color; }

	inline void setIntensity(const GLfloat& value)
	{
		if (value > 1.0) intensity = 1.0;
		else if (value < 0.0) intensity = 0.0;
		else intensity = value;
	}
	inline const GLfloat& getIntensity() { return intensity; }

protected:
	GLfloat intensity;
	glm::vec4 color;

};
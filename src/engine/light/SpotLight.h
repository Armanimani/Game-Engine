#pragma once

#include "Light.h"

class SpotLight : public Light
{
public:
	SpotLight(const std::string& name, const glm::vec3& position, const glm::vec3& color, const GLfloat& diffuseIntensity =  0.0, const GLfloat& specularIntensity = 0.0f,  const GLboolean& shadow = false) : Light(name, position, color, diffuseIntensity, specularIntensity, shadow) { type = LightType::spot; }
protected:
};
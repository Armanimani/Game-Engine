#pragma once
#include "Shader.h"

class SimpleDiffuseColorShader : public Shader
{
public:
	SimpleDiffuseColorShader();

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	GLuint location_color;
	virtual void getAllUniformLocations() override;
};
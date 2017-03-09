#pragma once
#include "Shader.h"

class SimpleColorShader : public Shader
{
public:
	SimpleColorShader();

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	virtual void getAllUniformLocations() override;
};
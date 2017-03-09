#pragma once
#include "Shader.h"

class SimplePositionShader : public Shader
{
public:
	SimplePositionShader();

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	virtual void getAllUniformLocations() override;
};
#pragma once
#include "Shader.h"


class BasicShader : public Shader
{
public:
	BasicShader();

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	virtual void getAllUniformLocations() override;
};
#pragma once
#include "Shader.h"


class BasicShader : public Shader
{
public:
	BasicShader();

	virtual void render(const std::shared_ptr<Mesh> mesh) override;
};
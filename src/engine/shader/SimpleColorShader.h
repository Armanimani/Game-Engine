#pragma once
#include "Shader.h"

class SimpleColorShader : public Shader
{
public:
	SimpleColorShader() : Shader(
		"SimpleColorShader",
		ShaderType::SimpleColorShader,
		"../src/engine/shader/glsl/SimpleColor.vert",
		"../src/engine/shader/glsl/SimpleColor.frag") {}

	virtual void render(const std::shared_ptr<Entity> entity) override;
};
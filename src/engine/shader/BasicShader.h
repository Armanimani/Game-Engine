#pragma once
#include "Shader.h"


class BasicShader : public Shader
{
public:
	BasicShader() : Shader(
		"BasicShader", 
		ShaderType::BasicShader, 
		"../src/engine/shader/glsl/Basic.vert", 
		"../src/engine/shader/glsl/Basic.frag") {}

	virtual void render(const std::shared_ptr<Entity> entity) override;
};
#pragma once
#include "Shader.h"

class SimplePositionShader : public Shader
{
public:
	SimplePositionShader() : Shader(
		"SimplePositionShader",
		ShaderType::SimplePositionShader,
		"../src/engine/shader/glsl/SimplePosition.vert",
		"../src/engine/shader/glsl/SimplePosition.frag") {}

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	virtual void loadAllToUniform(const std::shared_ptr<Entity> entity) override;
};
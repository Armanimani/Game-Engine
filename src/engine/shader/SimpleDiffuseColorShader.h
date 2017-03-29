#pragma once
#include "Shader.h"

class SimpleDiffuseColorShader : public Shader
{
public:
	SimpleDiffuseColorShader() : Shader(
		"SimpleDiffuseColorShader",
		ShaderType::SimpleDiffuseColorShader,
		"../src/engine/shader/glsl/SimpleDiffuseColor.vert",
		"../src/engine/shader/glsl/SimpleDiffuseColor.frag") {}

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	GLuint location_color;

	virtual void loadAllToUniform(const std::shared_ptr<Entity> entity) override;
	virtual void getAllUniformLocations() override;
};
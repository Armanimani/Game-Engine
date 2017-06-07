#pragma once
#include "Shader.h"

class SimpleTextureShader : public Shader
{
public:
	SimpleTextureShader() :Shader(
		"SimpleTextureShader",
		ShaderType::SimpleTextureShader,
		"../src/engine/shader/glsl/SimpleTexture.vert",
		"../src/engine/shader/glsl/SimpleTexture.frag") {}
	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	GLuint location_specularColor;
	GLuint location_Ka;
	GLuint location_Kd;
	GLuint location_Ks;
	GLuint location_shininess;

	virtual void loadAllToUniform(const std::shared_ptr<Entity> entity) override;
	virtual void getAllUniformLocations() override;

	virtual void prepareTextures() override;
};
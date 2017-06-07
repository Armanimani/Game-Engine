#pragma once
#include "Shader.h"

class SimpleDoubleTextureShader : public Shader
{
public:
	SimpleDoubleTextureShader() :Shader(
		"SimpleDoubleTextureShader",
		ShaderType::SimpleDoubleTextureShader,
		"../src/engine/shader/glsl/SimpleDoubleTexture.vert",
		"../src/engine/shader/glsl/SimpleDoubleTexture.frag") {}
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
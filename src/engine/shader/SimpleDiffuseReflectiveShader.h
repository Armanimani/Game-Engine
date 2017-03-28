#pragma once
#include "SimpleDiffuseColorShader.h"

class SimpleDiffuseReflectiveShader : public Shader
{
public:
	SimpleDiffuseReflectiveShader() : Shader(
		"SimpleDiffuseReflectiveShader",
		ShaderType::SimpleDiffuseReflectiveShader,
		"../src/engine/shader/glsl/SimpleDiffuseReflective.vert",
		"../src/engine/shader/glsl/SimpleDiffuseReflective.frag") {}

	virtual void render(const std::shared_ptr<Entity> entity) override;

protected:
	GLuint location_color;
	GLuint location_Kd;
	GLuint location_light;
	GLuint location_lightIntensity;
	GLuint location_normalMatrix;
	virtual void getAllUniformLocations() override;
	virtual void loadTransformationToUniform(const std::shared_ptr<Entity> entity) override;

	void loadLightsToUniform();
};
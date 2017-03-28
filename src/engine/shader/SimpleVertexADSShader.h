#pragma once
#include "Shader.h"

class SimpleVertexADSShader : public Shader
{
public:
	SimpleVertexADSShader() : Shader(
		"SimpleVertexADSShader",
		ShaderType::SimpleVertexADSShader,
		"../src/engine/shader/glsl/SimpleVertexADS.vert",
		"../src/engine/shader/glsl/SimpleVertexADS.frag") {}

	virtual void render(const std::shared_ptr<Entity> entity) override;
protected:
	GLuint location_color;
	GLuint location_Ka;
	GLuint location_Kd;
	GLuint location_Ks;
	GLuint location_shininess;

	virtual void getAllUniformLocations() override;
};

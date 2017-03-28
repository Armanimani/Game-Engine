#pragma once
#include "Shader.h"

class SimpleFragmentADS2FaceShader : public Shader
{
public:
	SimpleFragmentADS2FaceShader() : Shader(
		"SimpleFragmentADS2FaceShader",
		ShaderType::SimpleFragmentADS2FaceShader,
		"../src/engine/shader/glsl/SimpleFragmentADS2Face.vert",
		"../src/engine/shader/glsl/SimpleFragmentADS2Face.frag") {}
	virtual void render(const std::shared_ptr<Entity> entity) override;
protected:
	GLuint location_color;
	GLuint location_colorBack;
	GLuint location_Ka;
	GLuint location_Kd;
	GLuint location_Ks;
	GLuint location_shininess;

	virtual void getAllUniformLocations() override;
};
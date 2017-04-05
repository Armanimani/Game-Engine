#pragma once

#include "TextShader.h"

class SignedDistanceTextShader : public TextShader
{
public:
	SignedDistanceTextShader() : TextShader("SignedDistanceTextShader",
		ShaderType::SignedDistanceTextShader,
		"../src/engine/shader/text/glsl/SignedDistanceText.vert",
		"../src/engine/shader/text/glsl/SignedDistanceText.frag") {}

	virtual void render(const std::shared_ptr<GUITextModel> model);

protected:
	GLuint location_color;
	GLuint location_edge;
	GLuint location_width;

	virtual void loadAllToUniform(const std::shared_ptr<GUITextModel> model) override;
	virtual void getAllUniformLocations() override;
};
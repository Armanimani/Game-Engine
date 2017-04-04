#pragma once
#include "TextShader.h"

class SimpleTextShader : public TextShader
{
public:
	SimpleTextShader() : TextShader("SimpleTextShader",
		ShaderType::SimpleTextShader,
		"../src/engine/shader/text/glsl/SimpleText.vert",
		"../src/engine/shader/text/glsl/SimpleText.frag") {}

	virtual void render(const std::shared_ptr<GUITextModel> model);

protected:
	GLuint location_color;
	virtual void loadAllToUniform(const std::shared_ptr<GUITextModel> model) override;
	virtual void getAllUniformLocations() override;
};
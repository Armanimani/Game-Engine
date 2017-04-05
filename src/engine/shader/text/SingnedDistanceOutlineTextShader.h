#pragma once
#include "SingedDistanceTextShader.h"

class SignedDistanceOutlineTextShader : public SignedDistanceTextShader
{
public:
	SignedDistanceOutlineTextShader() : SignedDistanceTextShader()
	{
		name = "SignedDistanceOutlineTextShader";
		type = ShaderType::SignedDistanceOutlineTextShader;
		vertexShader = "../src/engine/shader/text/glsl/SignedDistanceOutlineText.vert";
		fragmentShader = "../src/engine/shader/text/glsl/SignedDistanceOutlineText.frag";
	}

protected:
	GLuint location_color;
	GLuint location_edge;
	GLuint location_width;
	GLuint location_outlineColor;
	GLuint location_outlineEdge;
	GLuint location_outlineWidth;
	GLuint location_outlineOffsetX;
	GLuint location_outlineOffsetY;


	virtual void loadAllToUniform(const std::shared_ptr<GUITextModel> model) override;
	virtual void getAllUniformLocations() override;
};
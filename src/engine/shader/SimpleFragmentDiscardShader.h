#pragma once

#include "SimpleFragmentADSShader.h"

class SimpleFragmentDiscardShader : public SimpleFragmentADSShader
{
public:
	SimpleFragmentDiscardShader() : SimpleFragmentADSShader()
	{
		name = "SimpleFragmentDiscardShader";
		type = ShaderType::SimpleFragmentDiscardShader;
		vertexShader = "../src/engine/shader/glsl/SimpleFragmentDiscard.vert";
		fragmentShader = "../src/engine/shader/glsl/SimpleFragmentDiscard.frag";
	}

	virtual void render(const std::shared_ptr<Entity> entity) override;
protected:
	GLuint location_discardScale;
	GLuint location_discardThickness;
	virtual void loadAllToUniform(const std::shared_ptr<Entity> entity) override;
	virtual void getAllUniformLocations() override;
};
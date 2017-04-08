#pragma once

#include "SimpleFragmentADSShader.h"

class SimpleFragmentADSToonShader : public SimpleFragmentADSShader
{
public:
	SimpleFragmentADSToonShader() : SimpleFragmentADSShader()
	{
		name = "SimpleFragmentADSToonShader";
		type = ShaderType::SimpleFragmentADSToonShader;
		vertexShader = "../src/engine/shader/glsl/SimpleFragmentADSToon.vert";
		fragmentShader = "../src/engine/shader/glsl/SimpleFragmentADSToon.frag";
	}
	virtual void render(const std::shared_ptr<Entity> entity) override;
protected:
	GLuint location_toonLevel;
	virtual void loadAllToUniform(const std::shared_ptr<Entity> entity) override;
	virtual void getAllUniformLocations() override;
};
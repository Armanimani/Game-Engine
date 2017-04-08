#pragma once

#include "SimpleFragmentADSShader.h"

class SimpleFogShader : public SimpleFragmentADSShader
{
public:
	SimpleFogShader() : SimpleFragmentADSShader()
	{
		name = "SimpleFogShader";
		type = ShaderType::SimpleFogShader;
		vertexShader = "../src/engine/shader/glsl/SimpleFog.vert";
		fragmentShader = "../src/engine/shader/glsl/SimpleFog.frag";
	}
};
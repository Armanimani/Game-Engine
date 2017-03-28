#pragma once
#include "SimpleVertexADSShader.h"

class SimpleFragmentADSShader : public SimpleVertexADSShader
{
public:
	SimpleFragmentADSShader() : SimpleVertexADSShader()
	{
		name = "SimpleFragmentADSShader";
		type = ShaderType::SimpleFragmentADSShader;
		vertexShader = "../src/engine/shader/glsl/SimpleFragmentADS.vert";
		fragmentShader = "../src/engine/shader/glsl/SimpleFragmentADS.frag";
	}
};

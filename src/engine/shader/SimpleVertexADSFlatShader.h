#pragma once

#include "SimpleVertexADSShader.h"

class SimpleVertexADSFlatShader : public SimpleVertexADSShader
{
public:
public:
	SimpleVertexADSFlatShader() : SimpleVertexADSShader()
	{
		name = "SimpleVertexADSFlatShader";
		type = ShaderType::SimpleVertexADSFlatShader;
		vertexShader = "../src/engine/shader/glsl/SimpleVertexADSFlat.vert";
		fragmentShader = "../src/engine/shader/glsl/SimpleVertexADSFlat.frag";
	}
};
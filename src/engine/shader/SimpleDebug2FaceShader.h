#pragma once

#include "SimpleFragmentADS2FaceShader.h"

class SimpleDebug2FaceShader : public SimpleFragmentADS2FaceShader
{
public:
	SimpleDebug2FaceShader() : SimpleFragmentADS2FaceShader()
	{
		name = "SimpleDebug2FaceShader";
		type = ShaderType::SimpleDebug2FaceShader;
		fragmentShader = "../src/engine/shader/glsl/SimpleDebug2Face.frag";
	}
};
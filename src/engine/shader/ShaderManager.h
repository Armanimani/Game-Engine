#pragma once
#include <memory>
#include <vector>
#include "Shader.h"

#include <unordered_map>

class ShaderManager
{
public:
	void init();
	void installShaders();
	void clearShaders();
	void cleanUp();
	std::shared_ptr<Shader> getShader(const ShaderType& type);
protected:
	std::unordered_map<ShaderType, std::shared_ptr<Shader>> shaderMap;
};
#pragma once
#include "../shader/ShaderType.h"
#include "../shader/Shader.h"
#include <memory>


class Material
{
public:
	Material(const std::string& name, const ShaderType& shaderType) : name(name), shaderType(shaderType) {}

	inline const ShaderType& getShaderType() { return shaderType; }
	inline const std::string& getName() { return name; }
	inline const std::shared_ptr<Shader> getShader() { return shader; }

protected:
	std::string name;
	ShaderType shaderType;
	std::shared_ptr<Shader> shader;
};
#pragma once
#include "../shader/ShaderType.h"
#include <string>
#include <memory>
#include "MaterialProperties.h"


class Material
{
public:
	Material(const std::string& name, const ShaderType& shaderType) : name(name), shaderType(shaderType) {}

	inline const ShaderType& getShaderType() { return shaderType; }
	inline const std::string& getName() { return name; }
	inline const MaterialProperties& getProperties() { return properties; }
	inline void setProperties(const MaterialProperties& props) { properties = props; }

protected:
	std::string name;
	ShaderType shaderType;
	MaterialProperties properties;
};
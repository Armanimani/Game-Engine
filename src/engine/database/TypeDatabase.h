#pragma once

#include "../mesh/MeshAttribute.h"
#include "../shader/ShaderType.h"
#include <string>

class TypeDatabase
{
public:
	static MeshAttribute getMeshAttributeType(const std::string& value);
	static ShaderType getShaderType(const std::string& value);

	static std::string getMeshAttributeTypeName(const MeshAttribute& value);
	static std::string getShaderTypeName(const ShaderType& value);
};
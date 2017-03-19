#pragma once

#include "../mesh/MeshAttribute.h"
#include "../shader/ShaderType.h"
#include "../shader/Shader.h"
#include <string>
#include "../camera/CameraType.h"
#include "../util/maps/BiMap.h"

class TypeDatabase
{
public:
	static MeshAttribute getMeshAttributeType(const std::string& value);
	static inline const ShaderType& getShaderType(const std::string& value) { return shaderMap.getCorrespondingElement(value); }
	static CameraType getCameraType(const std::string& value);

	static std::string getMeshAttributeTypeName(const MeshAttribute& value);
	static inline const std::string& getShaderTypeName(const ShaderType& value) { return shaderMap.getCorrespondingElement(value); }
	static const std::string getCameraTypeName(const CameraType& value);

	static inline void registerShaderType(std::shared_ptr<Shader> shader) { shaderMap.registerElement(shader->getType(), shader->getName()); }

protected:
	static BiMap<ShaderType, std::string> shaderMap;
};


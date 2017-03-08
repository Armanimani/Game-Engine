#include "TypeDatabase.h"
#include "../debug/Debug.h"

MeshAttribute TypeDatabase::getMeshAttributeType(const std::string & value)
{
	if (value == "position") return MeshAttribute::position;
	if (value == "color") return MeshAttribute::color;
	if (value == "normal") return MeshAttribute::normal;
	if (value == "texture") return MeshAttribute::texture;

	Debug::print(value);
	Debug::print("unable to recongnize the mesh attribute!");
	return MeshAttribute::noType;
}

ShaderType TypeDatabase::getShaderType(const std::string & value)
{
	if (value == "BasicShader") return ShaderType::BasicShader;
	if (value == "SimplePositionShader") return ShaderType::SimplePositionShader;
	if (value == "SimpleColorShader") return ShaderType::SimpleColorShader;
	if (value == "SimpleDiffuseColorShader") return ShaderType::SimpleDiffuseColorShader;

	Debug::print(value);
	Debug::print("unable to recongnize the shader Type!");
	return ShaderType::noType;
}

std::string TypeDatabase::getMeshAttributeTypeName(const MeshAttribute & value)
{
	if (value == MeshAttribute::position) return "position";
	if (value == MeshAttribute::color) return "color";
	if (value == MeshAttribute::normal) return "normal";
	if (value == MeshAttribute::texture) return "texture";
	
	Debug::print("unable to recongnize the mesh attribute!");
	return "noType";
}

std::string TypeDatabase::getShaderTypeName(const ShaderType & value)
{
	if (value == ShaderType::BasicShader) return "BasicShader";
	if (value == ShaderType::SimplePositionShader) return "SimplePositionShader";
	if (value == ShaderType::SimpleColorShader) return "SimpleColorShader";
	if (value == ShaderType::SimpleDiffuseColorShader) return "SimpleDiffuseColorShader";

	Debug::print("unable to recongnize the shader Type!");
	return "noType";
}


#include "TypeDatabase.h"
#include "../debug/Debug.h"

BiMap<ShaderType, std::string> TypeDatabase::shaderMap;

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


std::string TypeDatabase::getMeshAttributeTypeName(const MeshAttribute & value)
{
	if (value == MeshAttribute::position) return "position";
	if (value == MeshAttribute::color) return "color";
	if (value == MeshAttribute::normal) return "normal";
	if (value == MeshAttribute::texture) return "texture";
	
	Debug::print("unable to recongnize the mesh attribute!");
	return "noType";
}

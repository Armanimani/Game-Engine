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

CameraType TypeDatabase::getCameraType(const std::string & value)
{
	if (value == "free") return CameraType::free;
	if (value == "FPS") return CameraType::FPS;
	if (value == "arcBall") return CameraType::arcBall;

	Debug::print(value);
	Debug::print("unable to recognize the camera Type!");
	return CameraType::noType;
}

CameraProjectionType TypeDatabase::getCameraProjectionType(const std::string & value)
{
	if (value == "prespective") return CameraProjectionType::prespective;
	if (value == "orthogonal") return CameraProjectionType::orthogonal;

	Debug::print(value);
	Debug::print("unable to recognize the camera projection type!");
	return CameraProjectionType::noType;
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

const std::string TypeDatabase::getCameraTypeName(const CameraType & value)
{
	if (value == CameraType::noType) return "noType";
	if (value == CameraType::free) return "free";
	if (value == CameraType::FPS) return "FPS";
	if (value == CameraType::arcBall) return "arcBall";
	return "ERROR";
}

const std::string TypeDatabase::getCameraProjectionTypeName(const CameraProjectionType & value)
{
	if (value == CameraProjectionType::noType) return "noType";
	if (value == CameraProjectionType::prespective) return "prespective";
	if (value == CameraProjectionType::orthogonal) return "orthogonal";
	return "ERROR";
}

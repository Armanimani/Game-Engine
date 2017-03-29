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
	if (value == "orthoFree") return CameraType::orthoFree;
	if (value == "orthoFree2D") return CameraType::orthoFree2D;
	if (value == "target") return CameraType::target;

	Debug::print(value);
	Debug::print("unable to recognize the camera Type!");
	return CameraType::noType;
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
	if (value == CameraType::orthoFree) return "orthoFree";
	if (value == CameraType::orthoFree2D) return "orthoFree2D";
	if (value == CameraType::target) return "target";
	return "ERROR";
}

LightType TypeDatabase::getLightType(const std::string & value)
{
	if (value == "noType") return LightType::noType;
	if (value == "ambient") return LightType::ambient;
	if (value == "point") return LightType::point;
	if (value == "directional") return LightType::directional;
	if (value == "spot") return LightType::spot;

	Debug::print(value);
	Debug::print("unable to recognize the light Type!");
	return LightType::noType;
}

const std::string TypeDatabase::getLightTypeName(const LightType & value)
{
	if (value == LightType::noType) return "noType";
	if (value == LightType::ambient) return "ambient";
	if (value == LightType::point) return "point";
	if (value == LightType::directional) return "directional";
	if (value == LightType::spot) return "spot";
	return "ERROR";
}

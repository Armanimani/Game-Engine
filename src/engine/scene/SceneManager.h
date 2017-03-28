#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "../model/Model.h"
#include "../entity/Entity.h"
#include "../util/maps/UMap.h"
#include "../camera/CameraManager.h"
#include "../light/LightManager.h"

class SceneManager
{
public:
	SceneManager();

	UMap<Material> materialMap;
	UMap<Mesh> meshMap;
	UMap<Model> modelMap;
	UMap<Entity> entityMap;

	CameraManager cameraManager;
	LightManager lightManager;
	void cleanUp();

protected:
};

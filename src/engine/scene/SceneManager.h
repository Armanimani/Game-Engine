#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "../model/Model.h"
#include "../entity/Entity.h"
#include "../util/maps/UMap.h"

class SceneManager
{
public:
	SceneManager();

	UMap<Material> materialMap;
	UMap<Mesh> meshMap;
	UMap<Model> modelMap;
	UMap<Entity> entityMap;

	void cleanUp();

protected:
};

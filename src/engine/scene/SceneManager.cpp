#include "SceneManager.h"
#include "../debug/Debug.h"

SceneManager::SceneManager()
{
}

void SceneManager::cleanUp()
{
	meshMap.clearMap();
	materialMap.clearMap();
	modelMap.clearMap();
	entityMap.clearMap();
	cameraManager.cleanUp();
	lightManager.cleanUp();
}

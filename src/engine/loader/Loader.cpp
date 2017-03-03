#include "Loader.h"

void Loader::init(std::shared_ptr<SceneManager> manager)
{
	sceneManager = manager;
}

void Loader::load()
{
	for (auto it : sceneManager->meshMap.getMap())
	{
		it.second->load();
	}
}

#include "Loader.h"

void Loader::init(std::shared_ptr<SceneManager> manager)
{
	sceneManager = manager;
}

void Loader::load()
{
	for (auto it : sceneManager->fontManager.getMap())
	{
		it.second->getTexture()->load();
	}

	for (auto it : sceneManager->meshMap.getMap())
	{
		it.second->load();
	}
}

void Loader::loadGUIText()
{
	for (auto it : sceneManager->GUITextManager.getMap())
	{
		it.second->getMesh()->load();
	}
}

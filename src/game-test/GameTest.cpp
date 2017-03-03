#include "GameTest.h"

GameTest::GameTest()
{
	createScenes();
}

void GameTest::createScenes()
{
	std::shared_ptr<Scene> scene1 = std::make_shared<Scene>("begin");
	scenes.addItem(scene1);
}


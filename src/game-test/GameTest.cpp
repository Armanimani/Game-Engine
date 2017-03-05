#include "GameTest.h"

GameTest::GameTest()
{
	createScenes();
}

void GameTest::createScenes()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>("begin");
	scene->setDataFile("../res/scene/test.xml");
	scenes.addItem(scene);
}


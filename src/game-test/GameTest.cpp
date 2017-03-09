#include "GameTest.h"
#include "scenes\Scene1.h"

GameTest::GameTest()
{
	createScenes();
}

void GameTest::createScenes()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene1>("begin");
	scene->setDataFile("../res/scene/test.xml");
	scenes.addItem(scene);
}
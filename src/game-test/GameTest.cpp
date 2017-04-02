#include "GameTest.h"
#include "scenes\Scene1.h"
#include "scenes\Scene2.h"
#include "scenes\Scene3.h"
#include "scenes\Scene4.h"

GameTest::GameTest()
{
	createScenes();
}

void GameTest::createScenes()
{
	std::shared_ptr<Scene> scene;

	scene = std::make_shared<Scene1>("begin");
	scene->setDataFile("../res/scene/test2.xml");
	scenes.addItem(scene);

	scene = std::make_shared<Scene2>("scene2");
	scene->setDataFile("../res/scene/test2.xml");
	scenes.addItem(scene);

	scene = std::make_shared<Scene3>("scene3");
	scene->setDataFile("../res/scene/test2.xml");
	scenes.addItem(scene);

	scene = std::make_shared<Scene4>("scene4");
	scene->setDataFile("../res/scene/test2.xml");
	scenes.addItem(scene);
}
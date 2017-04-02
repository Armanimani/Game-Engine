#include <Windows.h>
#include <iostream>
#include "engine\Engine.h"
#include "game-test\GameTest.h"

#ifdef WIN32

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
{

	Engine engine;
	std::shared_ptr<GameTest> game = std::make_shared<GameTest>();
	std::shared_ptr<GameSettings> settings = std::make_shared<GameSettings>();
	settings->resX = 1920;
	settings->resy = 1080;
	game->setSettings(settings);
	engine.registerGame(game);
	engine.run();


	return 0;
}

#endif //WIN32
#include <Windows.h>
#include <iostream>
#include "engine\Engine.h"
#include "game-test\GameTest.h"

#ifdef WIN32

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
{

	Engine engine;
	std::shared_ptr<GameTest> game = std::make_shared<GameTest>();

	engine.registerGame(game);
	engine.run();


	return 0;
}

#endif //WIN32
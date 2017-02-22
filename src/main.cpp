#include <Windows.h>
#include <iostream>
#include "engine\Engine.h"

#ifdef WIN32

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
{
	Engine engine;
	engine.init();
	engine.run();
	engine.shutDown();

	return 0;
}

#endif //WIN32
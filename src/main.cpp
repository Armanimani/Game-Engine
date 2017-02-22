#include <Windows.h>
#include <iostream>
#include "engine\Engine.h"
#include "engine\scene\Scene.h"

#ifdef WIN32

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR szCmdLine, int CmdShow)
{
	Engine engine;
	Scene s;
	engine.init();
	engine.registerScene(s);
	engine.run();
	engine.shutDown();

	return 0;
}

#endif //WIN32
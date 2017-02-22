#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>
Engine::Engine()
{
	window = std::make_unique<Win32Window>();
}

void Engine::init()
{
	initConsole();

	window->init();
	window->createWindow();
	window->showWindow();
	window->setInputMapper(inMapper);
}

void Engine::run()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Sleep(100);
		//Debug::print(window->getMousePosition());
	}
}

void Engine::shutDown()
{
	window->killWinodw();
}

void Engine::registerScene(Scene& s)
{
	// TODO for now! 
	scene = &s;
	scene->setWindowHandle(window->getWindowHandle());
	inMapper.registerScene(s);
}

void Engine::initConsole()
{
#if _DEBUG
	AllocConsole();
	errno_t err;
	FILE *stream;
	err = freopen_s(&stream, "CONOUT$", "w+", stdout);
#endif

	Debug::init();
}

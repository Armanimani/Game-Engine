#include "Engine.h"
#include "debug\Debug.h"
Engine::Engine()
{
	window = std::make_unique<Win32Window>();
}

void Engine::init()
{
	initConsole();

	window->init();
}

void Engine::run()
{
	window->createWindow();
	window->showWindow();

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
	}
}

void Engine::shutDown()
{
	window->killWinodw();
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

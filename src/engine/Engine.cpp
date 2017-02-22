#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>

Engine::Engine()
{
	window = std::make_unique<Win32Window>();
	settings = std::make_unique<EngineSettings>();
	inMapper = std::make_shared<InputMapper>();
}

void Engine::init()
{
	initConsole();

	window->init();
	window->createWindow();
	window->showWindow();
	window->setInputMapper(inMapper);
	
	Clock::init();
	if (settings->max_FPS != -1)
	{
		renderInterval = 1.0 / settings->max_FPS;
	}
}

void Engine::run()
{
	MSG msg;
	Clock::prevRenderTime = Clock::getTime();

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
		
		Clock::getTime();
		if ( Clock::deltaTime >= renderInterval)
		{
			FPS = 1 / Clock::deltaTime;
			Clock::prevRenderTime = Clock::time;
			Debug::print(window->getGLMousePosition());
		}
	}
}

void Engine::shutDown()
{
	window->killWindow();
}

void Engine::registerScene(Scene& s)
{
	// TODO for now! 
	scene = &s;
	scene->setWindowHandle(window->getWindowHandle());
	inMapper->registerScene(s);
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

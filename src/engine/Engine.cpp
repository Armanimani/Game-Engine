#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>

#include <glew\GL\glew.h>

Engine::Engine()
{
	window = std::make_unique<Win32Window>();
	settings = std::make_unique<EngineSettings>();
	inMapper = std::make_shared<InputMapper>();
}

void Engine::init()
{
	initConsole();
	initWindow();
	initGL();
	initClock();
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
			renderGL();
			SwapBuffers(*hdc);
			calculateFPS();
			//Debug::print(window->getGLMousePosition());
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

void Engine::initGL()
{
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		Debug::print("glew Initialization failed!");
	}
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
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

void Engine::initWindow()
{
	window->init();
	window->createWindow();
	hdc = &window->getHDC();
	window->showWindow();
	window->setInputMapper(inMapper);
}

void Engine::initClock()
{
	Clock::init();
	if (settings->max_FPS != -1)
	{
		renderInterval = 1.0f / settings->max_FPS;
	}
}

void Engine::renderGL()
{

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Engine::calculateFPS()
{
	FPS = 1.0f / Clock::deltaTime;
	Clock::prevRenderTime = Clock::time;
}
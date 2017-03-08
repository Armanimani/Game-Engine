#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>
#include "shader\SimpleColorShader.h"
#include "shader\SimplePositionShader.h"
#include "mesh\Mesh.h"
#include "entity\Entity.h"
#include <algorithm>

#include <glew\GL\glew.h>

#include "fileController\SceneFileController.h"

Engine::Engine()
{
	window = std::make_unique<Win32Window>();
	settings = std::make_unique<EngineSettings>();
	inMapper = std::make_shared<InputMapper>();
	renderer = std::make_unique<Renderer>();
	sceneManager = std::make_shared<SceneManager>();
	loader = std::make_shared<Loader>();

	init();

}

void Engine::registerGame(const std::shared_ptr<Game> _game)
{
	game = _game;
	registerScene(game->getScene("begin"));
}

void Engine::run()
{
	load();

	unsigned short int FPSCounter = 0;

	MSG msg;
	Clock::prevTime = Clock::getTime();

	while (isRunning)
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
		if ( Clock::deltaTime >= logicInterval)
		{
			Clock::prevTime = Clock::time;
			calculateFPS(FPSCounter);
			scene->update();
			handleEngineEvents();
			//Debug::print(window->getGLMousePosition());
		}
		renderGL();
		SwapBuffers(*hdc);
		
		FPSCounter++;
	}
	shutdown();
}

void Engine::init()
{
	initConsole();
	initWindow();
	initGL();
	initClock();
	initRenderer();
	initLoader();
}

void Engine::shutdown()
{
	Debug::print("Shutting Down...");
	SceneFileController::writeSceneDataFile(sceneManager, "../res/scene/finalState.xml");
	renderer->cleanUp();
	sceneManager->cleanUp();
	window->killWindow();
}

void Engine::registerScene(std::shared_ptr<Scene> s)
{
	// TODO for now! 
	scene = s;
	scene->setWindowHandle(window->getWindowHandle());
	scene->setEngineEventList(eventList);
	scene->setDelayedEngineEventList(delayedEventList);
	inMapper->registerScene(s);
}

void Engine::initGL()
{
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		Debug::print("glew Initialization failed!");
	}

	glClearColor(settings->backgroundColor.r, settings->backgroundColor.g, settings->backgroundColor.b, settings->backgroundColor.a);
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
	if (settings->logicFreq != 0)
	{
		logicInterval = 1.0f / settings->logicFreq;
	}
}

void Engine::initRenderer()
{
	renderer->init(sceneManager);
	renderer->installShaders();
}

void Engine::initLoader()
{
	loader->init(sceneManager);
}

void Engine::load()
{
	SceneFileController::readSceneDataFile(sceneManager, scene->getDataFile());
	loader->load();
}

void Engine::renderGL()
{
	glClearColor(settings->backgroundColor.r, settings->backgroundColor.g, settings->backgroundColor.b, settings->backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer->render();

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::calculateFPS(unsigned short int& FPSCounter)
{
	FPS = static_cast<unsigned short int> (FPSCounter / Clock::deltaTime);
	FPSCounter = 0;
	//Debug::print(std::to_string(FPS));
}


void Engine::handleEngineEvents()
{
	handleEvents();
	handleDelayedEvents();
}

void Engine::handleEvents()
{
	while (eventList.size() != 0)
	{
		std::shared_ptr<engine::Event> event = eventList.front();

		switch (eventList.front()->code)
		{
		case(engine::EventCode::shutdown):
		{
			isRunning = false;
			break;
		}
		case(engine::EventCode::changeBackground):
		{
			std::shared_ptr<engine::ChangeBackgroundEvent> e = std::static_pointer_cast<engine::ChangeBackgroundEvent> (event);
			settings->backgroundColor = e->data;
			break;
		}
		}
		eventList.pop();
	}

}

void Engine::handleDelayedEvents()
{
	double time = Clock::time;
	for (auto i = delayedEventList.begin(); i != delayedEventList.end(); ++i)
	{
		if ((*i)->execTime <= time)
		{
			switch ((*i)->code)
			{
			case (engine::EventCode::shutdown):
			{
				isRunning = false;
				break;
			}
			case (engine::EventCode::changeBackground):
			{
				std::shared_ptr<engine::DelayedChangeBackgroundEvent> e = std::static_pointer_cast<engine::DelayedChangeBackgroundEvent> (*(i));
				settings->backgroundColor = e->color;
				break;
			}
			}
			i = delayedEventList.erase(i);
			if (i == delayedEventList.cend()) break;
		}
	}

}

#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>
#include "shader\SimpleColorShader.h"
#include "shader\SimplePositionShader.h"
#include "mesh\Mesh.h"
#include "entity\Entity.h"

#include <glew\GL\glew.h>

#include "fileController\SceneFileController.h"

void test()
{
	
	//for (rapidxml::xml_node<> *pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
	//{
	//	std::cout << pNode->value() << std::endl;
	//}
}

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

	MSG msg;
	Clock::prevRenderTime = Clock::getTime();

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
		handleEvents();
		Clock::getTime();
		if ( Clock::deltaTime >= renderInterval)
		{
			renderGL();
			SwapBuffers(*hdc);
			calculateFPS();
			//Debug::print(window->getGLMousePosition());
		}
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
	if (settings->max_FPS != 0)
	{
		renderInterval = 1.0f / settings->max_FPS;
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

void Engine::calculateFPS()
{
	FPS = 1.0f / Clock::deltaTime;
	Clock::prevRenderTime = Clock::time;
	//Debug::print(std::to_string(FPS));
}


void Engine::handleEvents()
{
	while (eventList.size() != 0)
	{
		std::shared_ptr<EngineEvent> event = eventList.front();

		switch (eventList.front()->code)
		{
		case(EngineEventCode::shutdown):
		{
			isRunning = false;
			break;
		}
		case(EngineEventCode::changeBackground):
		{
			settings->backgroundColor = event->vec4Data;
			break;
		}
		}
		eventList.pop();
	}

}
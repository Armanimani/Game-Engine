#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>
#include "shader\SimpleColorShader.h"
#include "shader\SimplePositionShader.h"
#include "mesh\Mesh.h"
#include "entity\Entity.h"

#include <glew\GL\glew.h>

#include "fileController\MaterialFileController.h"

Engine::Engine()
{
	window = std::make_unique<Win32Window>();
	settings = std::make_unique<EngineSettings>();
	inMapper = std::make_shared<InputMapper>();
	renderer = std::make_unique<Renderer>();
	sceneManager = std::make_shared<SceneManager>();
	loader = std::make_shared<Loader>();

	init();

	std::shared_ptr<Material> mat = MaterialFileController::readFile("C:/Users/Arman/Documents/test.mat");
	MaterialFileController::writeFile("C:/Users/Arman/Documents/test2.mat", mat);
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
	initRender();
}

void Engine::shutdown()
{
	Debug::print("Shutting Down...");
	renderer->cleanUp();
	sceneManager->cleanUp();
	window->killWindow();
}

void Engine::registerScene(std::shared_ptr<Scene> s)
{
	// TODO for now! 
	scene = s;
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

void Engine::initRenderer()
{
	renderer->init(sceneManager);
	renderer->installShaders();
}

void Engine::initLoader()
{
	loader->init(sceneManager);
}

void Engine::initRender()
{
	//
	std::vector<GLfloat> verts
	{
		-0.8f, -0.8f, +0.0f,
		+1.0f, +0.0f, +0.0f,
		+0.8f, -0.8f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +0.8f, +0.0f,
		+0.0f, +0.0f, +1.0f};

	std::vector<GLfloat> verts2
	{
		-0.5f, +0.5f, +0.0f,
		-0.5f, -0.5f, +0.0f,
		+0.5f, -0.5f, +0.0f,
		+0.5f, +0.5f, +0.0f
	};

	std::vector<GLuint> indices {0, 1, 2};
	std::vector<GLuint> indices2
	{
		0, 1, 3,
		3, 1, 2
	};
	std::vector<MeshAttribute> attribs {MeshAttribute::position, MeshAttribute::color};
	std::vector<MeshAttribute> attribs2 {MeshAttribute::position};
	std::shared_ptr<Mesh> mesh1 = std::make_shared<Mesh>("mesh1", verts, indices, attribs);
	std::shared_ptr<Mesh> mesh2 = std::make_shared<Mesh>("mesh2", verts2, indices2, attribs2);
	sceneManager->meshMap.addItem(mesh1);
	sceneManager->meshMap.addItem(mesh2);
	std::shared_ptr<Material> mat1 = std::make_shared<Material>("mat1", ShaderType::SimplePositionShader);
	std::shared_ptr<Material> mat2 = std::make_shared<Material>("mat2", ShaderType::SimpleColorShader);
	sceneManager->materialMap.addItem(mat1);
	sceneManager->materialMap.addItem(mat2);
	std::shared_ptr<Model> model1 = std::make_shared<Model>("model", sceneManager->meshMap.getItem("mesh1"), sceneManager->materialMap.getItem("mat2"));
	std::shared_ptr<Model> model2 = std::make_shared<Model>("model2", sceneManager->meshMap.getItem("mesh1"), sceneManager->materialMap.getItem("mat2"));
	sceneManager->modelMap.addItem(model1);
	sceneManager->modelMap.addItem(model2);
	//TODO

	std::shared_ptr<Entity> entity = std::make_shared<Entity>("test", model1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	sceneManager->entityMap.addItem(entity);


	//
}

void Engine::load()
{
	loader->load();
}

void Engine::renderGL()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer->render();

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::calculateFPS()
{
	FPS = 1.0f / Clock::deltaTime;
	Clock::prevRenderTime = Clock::time;
}
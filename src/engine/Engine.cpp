#include "Engine.h"
#include "debug\Debug.h"
#include <conio.h>
#include "shader\SimpleColorShader.h"
#include "shader\SimplePositionShader.h"
#include "mesh\Mesh.h"
#include "entity\Entity.h"

#include <glew\GL\glew.h>

std::shared_ptr<SimpleColorShader> shaderSC = std::make_shared<SimpleColorShader>();
std::shared_ptr<SimplePositionShader> shaderSP = std::make_shared<SimplePositionShader>();
Entity entity;

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
	shaderSC->cleanUp();
	shaderSP->cleanUp();
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

	shaderSC->install();
	shaderSP->install();

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

	std::vector<GLuint> indices{0, 1, 2};
	std::vector<GLuint> indices2
	{
		0, 1, 3,
		3, 1, 2
	};
	std::vector<MeshAttribute> attribs {MeshAttribute::position, MeshAttribute::color};
	std::vector<MeshAttribute> attribs2 {MeshAttribute::position};
	std::shared_ptr<Mesh> mesh1 = std::make_shared<Mesh> ("test", verts, indices, attribs);
	std::shared_ptr<Mesh> mesh2 = std::make_shared<Mesh>("test", verts2, indices2, attribs2);
	std::shared_ptr<Material> mat1 = std::make_shared<Material>(shaderSP);
	std::shared_ptr<Material> mat2 = std::make_shared<Material>(shaderSC);
	std::shared_ptr<Model> model1 = std::make_shared<Model>(mesh1, mat2);
	std::shared_ptr<Model> model2 = std::make_shared<Model>(mesh2, mat2);
	entity = Entity(model1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	
	entity.load();


	//


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

	entity.render();

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::calculateFPS()
{
	FPS = 1.0f / Clock::deltaTime;
	Clock::prevRenderTime = Clock::time;
}
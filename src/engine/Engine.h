#pragma once

#include <glew\GL\glew.h>

#include <memory>
#include "window\win32\Win32Window.h"
#include "userInput\inputMapper\InputMapper.h"
#include "scene\Scene.h"
#include "clock\Cock.h"
#include "settings\EngineSettings.h"
#include "renderer\Renderer.h"
#include "scene\SceneManager.h"
#include "loader\Loader.h"
#include "game\Game.h"

class Engine
{
public:
	Engine();
	void registerGame(const std::shared_ptr<Game> game);
	void run();


protected:
	void init();
	void shutdown();
	std::unique_ptr<Win32Window> window;
	std::shared_ptr<InputMapper> inMapper;
	std::unique_ptr<Renderer> renderer;
	std::shared_ptr<SceneManager> sceneManager;
	std::shared_ptr<Loader> loader;

	std::shared_ptr<Game> game;
	std::shared_ptr<Scene> scene;
	std::unique_ptr<EngineSettings> settings;
	
	float renderInterval = 0;
	unsigned short int FPS = 0;

	const HDC* hdc;

	void initGL();
	void initConsole();
	void initWindow();
	void initClock();
	void initRenderer();
	void initLoader();
	void initRender();
	
	void load();

	void renderGL();

	void calculateFPS();

	void registerScene(std::shared_ptr<Scene> s);
};
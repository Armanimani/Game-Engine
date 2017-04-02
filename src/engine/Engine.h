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
#include <queue>
#include "event\EngineEvent.h"
#include <unordered_set>
#include "event\DelayedEngineEvent.h"
#include "viewport\ViewportManager.h"

class Engine
{
public:
	Engine();
	void registerGame(const std::shared_ptr<Game> game);
	void run();

protected:
	void init();
	void shutdown();
	void update();
	bool isRunning = true;
	std::unique_ptr<Win32Window> window;
	std::shared_ptr<InputMapper> inMapper;
	std::unique_ptr<Renderer> renderer;
	std::shared_ptr<SceneManager> sceneManager;
	std::shared_ptr<Loader> loader;
	std::shared_ptr<ViewportManager> viewportManager;

	std::shared_ptr<Game> game;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<EngineSettings> settings;

	std::queue<std::shared_ptr<engine::Event>> eventList;
	std::unordered_set<std::shared_ptr<engine::DelayedEvent>> delayedEventList;
	
	float logicInterval = 0.0f;
	unsigned short int FPS;

	const HDC* hdc;

	void initGL();
	void initConsole();
	void initWindow();
	void initClock();
	void initRenderer();
	void initLoader();
	
	void load();

	void renderGL();

	void calculateFPS(unsigned short int& FPS);

	void registerScene(std::shared_ptr<Scene> s);
	void handleEngineEvents();
	void handleEvents();
	void handleDelayedEvents();
};
#pragma once

#include <glew\GL\glew.h>

#include <memory>
#include "window\win32\Win32Window.h"
#include "userInput\inputMapper\InputMapper.h"
#include "scene\Scene.h"
#include "clock\Cock.h"
#include "settings\EngineSettings.h"

class Engine
{
public:
	Engine();
	void init();
	void run();
	void shutDown();

	void registerScene(Scene& s);

protected:
	std::unique_ptr<Win32Window> window;
	std::shared_ptr<InputMapper> inMapper;
	Scene* scene;
	std::unique_ptr<EngineSettings> settings;
	
	float renderInterval = 0;
	unsigned short int FPS = 0;

	const HDC* hdc;

	void initGL();
	void initConsole();
	void initWindow();
	void initClock();
	
	void renderGL();

	void calculateFPS();
};
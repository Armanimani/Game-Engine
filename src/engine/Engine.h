#pragma once

#include <memory>
#include "window\win32\Win32Window.h"
#include "userInput\inputMapper\InputMapper.h"
#include "scene\Scene.h"

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
	InputMapper inMapper;
	Scene* scene;

	void initConsole();
};
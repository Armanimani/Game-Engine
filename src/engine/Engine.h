#pragma once
#include "window\win32\Win32Window.h"
#include <memory>

class Engine
{
public:
	Engine();
	void init();
	void run();
	void shutDown();

protected:
	std::unique_ptr<Win32Window> window;

	void initConsole();
};
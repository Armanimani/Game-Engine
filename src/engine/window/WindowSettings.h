#pragma once
#include <string>
#include "../util/vector/USIVec2.h"

struct WindowSettings
{	
	std::string title = "Game";
	USIVec2 windowResolution {800, 600};
	USIVec2 monitorResolution {0, 0};
	USIVec2 windowPosition {0, 0};
	
	bool fullscreen = false;
	bool mouseLocked = false;
	bool mouseVisible = false;
};
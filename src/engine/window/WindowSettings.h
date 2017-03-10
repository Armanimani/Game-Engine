#pragma once
#include <string>
#include "../util/vector/USIVec2.h"
#include <Windows.h>

struct WindowSettings
{	
	std::string title = "Game";
	USIVec2 windowResolution {1000, 1000};
	USIVec2 monitorResolution {0, 0};
	USIVec2 windowPosition {0, 0};
	
	bool fullscreen = false;
	bool mouseLocked = false;
	bool mouseVisible = true;

	BYTE colorBits = 32;
	BYTE depthBufferBits = 16;
	BYTE alphaBuffer = 0;
	BYTE shiftBit = 0;
	BYTE accumulationBuffer = 0;
	BYTE stencilBuffer = 0;
	BYTE auxiliaryBuffer = 0;
};
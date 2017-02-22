#pragma once
#include <Windows.h>

class Clock
{
public:
	Clock() {};
	static void init();
	static float getTime();
	
	static float time;
	static float prevRenderTime;

	static float deltaTime;

protected:
	static LARGE_INTEGER timeFrequency;
	static LARGE_INTEGER startingTime;
};
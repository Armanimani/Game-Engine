#include "Cock.h"

LARGE_INTEGER Clock::timeFrequency;
LARGE_INTEGER Clock::startingTime;
float Clock::time;
float Clock::prevTime;
float Clock::deltaTime;

void Clock::init()
{
	QueryPerformanceFrequency(&timeFrequency);
	QueryPerformanceCounter(&startingTime);
}

float Clock::getTime()
{
	LARGE_INTEGER newTime;
	QueryPerformanceCounter(&newTime);
	time = (float)(newTime.QuadPart - startingTime.QuadPart) / (timeFrequency.QuadPart);
	
	deltaTime = time - prevTime;
	return time;
}

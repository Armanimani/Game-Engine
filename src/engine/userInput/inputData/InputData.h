#pragma once

#include <glm\glm.hpp>

struct InputData
{
	InputData() { for (auto i = 0; i != 256; ++i) keys[i] = false; }
	
	glm::vec2 mousePrevPosL;
	glm::vec2 mousePrevPosR;
	glm::vec2 mousePrevPosM;

	glm::vec2 mouseDragL;
	glm::vec2 mouseDragR;
	glm::vec2 mouseDragM;

	unsigned short int mouseWheelDelta = 0;
	bool keys[256];
};
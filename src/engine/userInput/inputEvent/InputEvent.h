#pragma once
#include "InputEventType.h"
#include "../keyCode/KeyCode.h"
#include <Windows.h>

struct InputEvent
{
	KeyCode key = KeyCode::NO_CODE;
	InputEventType type = InputEventType::NO_EVENT;

	bool altDown = false;
	bool ctrlDown = false;
	bool shiftDown = false;

	bool mouseLDown = false;
	bool mouseRDown = false;
	bool mouseMDown = false;

	HWND hwnd;

	short int posX = 0;
	short int posY = 0;
	short int wheelDelta = 0;
};

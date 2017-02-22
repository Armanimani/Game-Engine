#pragma once
#include <Windows.h>
#include "../../inputEvent/InputEvent.h"

class Win32RawInput
{
public:
	Win32RawInput() = delete;
	static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
protected:
	static void createKeyInputEvent(InputEvent& event, HWND hwnd, WPARAM wparam, LPARAM lparam);
	static void createMouseInputEvent(InputEvent& event, HWND hwnd, WPARAM wparam, LPARAM lparam);
};
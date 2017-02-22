#include "Win32RawInput.h"
#include <iostream>
#include "../../../debug/Debug.h"
#include<windowsx.h>

LRESULT CALLBACK Win32RawInput::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	InputEvent event;

	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		event.type = InputEventType::MOUSEL_DOWN;
		createMouseInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		event.type = InputEventType::MOUSEL_UP;
		createMouseInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		event.type = InputEventType::MOUSER_DOWN;
		createMouseInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_RBUTTONUP:
	{
		event.type = InputEventType::MOUSER_UP;
		createMouseInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_MBUTTONDOWN:
	{
		event.type = InputEventType::MOUSEM_DOWN;
		createMouseInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_MBUTTONUP:
	{
		event.type = InputEventType::MOUSEM_UP;
		createMouseInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_KEYDOWN:
	{
		event.type = InputEventType::KEY_DOWN;
		createKeyInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_KEYUP:
	{
		event.type = InputEventType::KEY_UP;
		createKeyInputEvent(event, hwnd, wparam, lparam);

		Debug::print(event);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Win32RawInput::createKeyInputEvent(InputEvent & event, HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	event.altDown = GetKeyState(VK_MENU) & 0x8000;
	event.ctrlDown = GetKeyState(VK_CONTROL) & 0x8000;
	event.shiftDown = GetKeyState(VK_SHIFT) & 0x8000;
	event.hwnd = hwnd;
	event.key = (KeyCode) wparam;
}

void Win32RawInput::createMouseInputEvent(InputEvent & event, HWND hwnd, WPARAM wparam, LPARAM lparam)
{
	event.altDown = GetKeyState(VK_MENU) & 0x8000;
	event.ctrlDown = GetKeyState(VK_CONTROL) & 0x8000;
	event.shiftDown = GetKeyState(VK_SHIFT) & 0x8000;
	event.hwnd = hwnd;

	event.mouseLDown = wparam & MK_LBUTTON;
	event.mouseRDown = wparam & MK_RBUTTON;
	event.mouseMDown = wparam & MK_MBUTTON;

	event.posX = GET_X_LPARAM(lparam);
	event.posY = GET_Y_LPARAM(lparam);
}

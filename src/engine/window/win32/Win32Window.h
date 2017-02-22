#pragma once
#include "../Window.h"

class Win32Window : public Window
{
public:
	void init() override;
	void createWindow() override;
	void showWindow() override;
	void killWinodw() override;

protected:
	static bool initialized;
	static HINSTANCE hInstance;

	HWND hWnd;

	static void staticInit();
};
#pragma once

#include <glew\GL\glew.h>
#include "../Window.h"
#include "../../userInput/inputEvent/InputEvent.h"

class Win32Window : public Window
{
public:
	Win32Window() : Window() {}
	void init() override;
	void createWindow() override;
	void showWindow() override;
	void killWindow() override;

	inline const HWND& getWindowHandle();

	virtual void setWindowTitle(const std::string& title) override;

	const std::shared_ptr<USIVec2> getMousePosition() const override;
	void showMouse(const bool& state = true) override;
	void lockMouse(const bool& state = true) override;

	void setWindowResolution(const unsigned short int& resX, unsigned short int& resY) override;
	const std::shared_ptr<USIVec2> getMonitorResolution() override;

	void setFullscreen(const bool state = true) override;
	void setFocus(const bool& state = true) override;
	const bool isFocused() override;

	inline const HDC& getHDC();

	static LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

protected:
	static bool initialized;
	static HINSTANCE hInstance;
	static void createKeyInputEvent(InputEvent& event, HWND hwnd, WPARAM wparam, LPARAM lparam);
	static void createMouseInputEvent(InputEvent& event, HWND hwnd, WPARAM wparam, LPARAM lparam);

	bool shown = false;

	HWND hWnd = NULL;
	HGLRC hRC = NULL;
	HDC hDC = NULL;
	GLuint pixelFormat;

	static void staticInit();
};

const HWND& Win32Window::getWindowHandle()
{
	return hWnd;
}

const HDC& Win32Window::getHDC()
{
	return hDC;
}
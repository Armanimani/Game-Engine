#pragma once
#include <Windows.h>
#include "../userInput/inputEvent/InputEvent.h"
#include "../userInput/inputEvent/InputHandlerCode.h"

class Scene
{
public:
	inline void setWindowHandle(const HWND& hwnd);
	void handleInputEvent(const InputEvent& event, const InputHandlerCode& code);
	inline const HWND& getWindowHandle() const;
protected:
	const HWND* hWnd;
};

const HWND& Scene::getWindowHandle() const
{
	return *hWnd;
}
void Scene::setWindowHandle(const HWND& hwnd)
{
	hWnd = &hwnd;
}
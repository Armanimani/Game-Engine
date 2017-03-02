#pragma once
#include <Windows.h>
#include "../userInput/inputEvent/InputEvent.h"
#include "../userInput/inputEvent/InputHandlerCode.h"
#include <vector>
#include "../model/Model.h"

class Scene
{
public:
	inline void setWindowHandle(const HWND& hwnd);
	void handleInputEvent(const InputEvent& event, const InputHandlerCode& code);
	inline const HWND& getWindowHandle() const;

protected:
	const HWND* hWnd;
	std::vector<Model> models;
};

const HWND& Scene::getWindowHandle() const
{
	return *hWnd;
}
void Scene::setWindowHandle(const HWND& hwnd)
{
	hWnd = &hwnd;
}
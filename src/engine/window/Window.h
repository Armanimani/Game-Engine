#include <Windows.h>
#include <memory>
#include "WindowSettings.h"
#include "../util/vector/USIVec2.h"
#include "../util/vector/FVec2.h"
#include "../userInput/inputMapper/InputMapper.h"
#include <iostream>


class Window
{
public:
	virtual void init() = 0;

	inline void setInputMapper(InputMapper& mapper);

	virtual void createWindow() = 0;
	virtual void showWindow() = 0;
	virtual void killWinodw() = 0;

	virtual void setWindowTitle(const std::string& title) = 0;
	inline virtual const std::string& getWindowTitle() const;

	virtual const std::shared_ptr<USIVec2> getMousePosition() const = 0;
	inline virtual const std::shared_ptr<FVec2> getGLMousePosition() const;
	virtual void showMouse(const bool& state = true) = 0;
	inline virtual const bool mouseIsVisible() const;
	virtual void lockMouse(const bool& state = true) = 0;
	inline virtual const bool mouseIsLocked() const;

	virtual void setWindowResolution(const unsigned short int& resX, unsigned short int& resY) = 0;
	inline virtual const std::shared_ptr<USIVec2> getWindowResolution() const;

	virtual const std::shared_ptr<USIVec2> getMonitorResolution() const = 0;

	virtual void setFullscreen(const bool state = true) = 0;
	inline virtual const bool isFullscreen() const;

	virtual void setFocus(const bool& state = true) = 0;
	virtual const bool isFocused() = 0;

	inline const WindowSettings& getSettings() const;

protected:
	WindowSettings settings;
	static InputMapper* inMapper;
};

void Window::setInputMapper(InputMapper& mapper)
{
	inMapper = &mapper;
}

const std::string& Window::getWindowTitle() const
{
	return settings.title;
}

const std::shared_ptr<FVec2> Window::getGLMousePosition() const
{
	std::shared_ptr<USIVec2> pos = getMousePosition();
	std::shared_ptr<USIVec2> res = getWindowResolution();

	std::shared_ptr<FVec2> ret = std::make_shared<FVec2>(2 * pos->x / (float) res->x - 1.0f, -2 * pos->y / (float) res->y + 1.0f); // TODO check for optimized version
	return ret;
}

const bool Window::mouseIsLocked() const
{
	return settings.mouseLocked;
}

const bool Window::mouseIsVisible() const
{
	return settings.mouseVisible;
}

const std::shared_ptr<USIVec2> Window::getWindowResolution() const
{
	std::shared_ptr<USIVec2> ret = std::make_shared<USIVec2>(settings.windowResolution.x, settings.windowResolution.y);
	//TODO look for optimized version
	return ret;
}

const bool Window::isFullscreen() const
{
	return settings.fullscreen;
}

const WindowSettings& Window::getSettings() const
{
	return settings;
}
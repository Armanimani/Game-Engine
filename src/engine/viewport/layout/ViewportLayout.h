#pragma once
#include "../../window/WindowSettings.h"
#include "ViewportLayoutType.h"
#include "../Viewport.h"
#include <vector>
#include <memory>

class ViewportLayout
{
public:
	ViewportLayout(const std::shared_ptr<WindowSettings> settings, const ViewportLayoutType& type = ViewportLayoutType::noType) : type(type), windowSettings(settings) {}
	virtual void initLayout(std::vector<std::shared_ptr<Viewport>>& map, const std::vector<std::shared_ptr<Camera>> cams) {};
	virtual void updateLayout(std::vector<std::shared_ptr<Viewport>>& map) {};
	inline const GLuint& getWindowResolutionX() { return windowSettings->windowResolution.x; }
	inline const GLuint& getWindowResolutionY() { return windowSettings->windowResolution.y; }

protected:
	ViewportLayoutType type;
	std::shared_ptr<WindowSettings> windowSettings;
};
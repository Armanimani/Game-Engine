#pragma once

#include "Scene1.h"

class Scene3 : public Scene1
{
public:
	Scene3(const std::string& name) : Scene1(name) {}
	virtual void setViewports(const std::shared_ptr<WindowSettings> windowSettings) override;
};
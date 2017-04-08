#pragma once

#include "Scene1.h"

class Scene2 : public Scene1
{
public:
	Scene2(const std::string& name) : Scene1(name) {}
	virtual void setViewports() override;
};
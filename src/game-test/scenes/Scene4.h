#pragma once
#include "Scene1.h"

class Scene4 : public Scene1
{
public:
	Scene4(const std::string& name) : Scene1(name) {}
	virtual void setViewports() override;
};
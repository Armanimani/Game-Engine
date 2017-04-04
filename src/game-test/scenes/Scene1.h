#pragma once

#include "../../engine/scene/Scene.h"

class Scene1 : public Scene
{
public:
	Scene1(const std::string& name) : Scene(name) {}
	virtual void handleInputEvent(const InputEvent& event, const InputHandlerCode& code) override;

	virtual void update() override;

	virtual void loadGUIText() override;
	
protected:
	virtual void handleInputKeys() override;
};
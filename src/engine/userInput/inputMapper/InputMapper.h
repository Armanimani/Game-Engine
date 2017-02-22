#pragma once
#include <vector>
#include "../../scene/Scene.h"
#include "../inputEvent/InputEvent.h"
#include "../inputEvent/InputHandlerCode.h"

class InputMapper
{
public:
	//TODO add a mapping function to be able to unregister scenes
	void registerScene(Scene& scene);
	const int registerEvent(const InputEvent& event, const InputHandlerCode& code);
private:
	std::vector<Scene*> scenes;
};
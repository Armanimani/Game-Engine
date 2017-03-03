#pragma once
#include <vector>
#include "../../scene/Scene.h"
#include "../inputEvent/InputEvent.h"
#include "../inputEvent/InputHandlerCode.h"
#include <memory>

class InputMapper
{
public:
	//TODO add a mapping function to be able to unregister scenes
	void registerScene(std::shared_ptr<Scene> scene);
	void clearScenes();
	const int registerEvent(const InputEvent& event, const InputHandlerCode& code);
private:
	std::vector<std::shared_ptr<Scene>> scenes;
};
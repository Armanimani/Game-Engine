#pragma once
#include "../scene/Scene.h"
#include "../util/maps/UMap.h"

class Game
{
public:
	Game();
	std::shared_ptr<Scene> getScene(const std::string& name);

protected:
	UMap<Scene> scenes;

	virtual void createScenes() = 0;
};
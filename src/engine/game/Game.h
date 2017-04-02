#pragma once
#include "../scene/Scene.h"
#include "../util/maps/UMap.h"
#include "../settings/GameSettings.h"

class Game
{
public:
	Game();
	std::shared_ptr<Scene> getScene(const std::string& name);

	inline void setSettings(const std::shared_ptr<GameSettings> value) { settings = value; }
	inline const std::shared_ptr<GameSettings> getSettings() { return settings; }

protected:
	UMap<Scene> scenes;
	std::shared_ptr<GameSettings> settings;

	virtual void createScenes() = 0;
};
#pragma once
#include "../scene/SceneManager.h"
#include "../window/WindowSettings.h"

class SceneFileController
{
public:
	static void readSceneDataFile(std::shared_ptr<SceneManager> manager, const std::shared_ptr<WindowSettings> windowSettings, const std::string& file);
	static void writeSceneDataFile(std::shared_ptr<SceneManager> manager, const std::string& file);
};
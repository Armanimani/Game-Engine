#pragma once
#include <memory>
#include "../scene/SceneManager.h"

class Loader
{
public:
	void init(std::shared_ptr<SceneManager> manager);
	void load(); //TODO: only laod the used models

protected:
	std::shared_ptr<SceneManager> sceneManager;
};
#include "Game.h"

Game::Game()
{
	settings = std::make_shared<GameSettings>();
}

std::shared_ptr<Scene> Game::getScene(const std::string& name)
{
	return scenes.getItem(name);
}

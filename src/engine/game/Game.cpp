#include "Game.h"

Game::Game()
{
}

std::shared_ptr<Scene> Game::getScene(const std::string& name)
{
	return scenes.getItem(name);
}

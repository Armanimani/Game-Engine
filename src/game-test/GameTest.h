#pragma once
#include "../engine/game/Game.h"

class GameTest : public Game
{
public:
	GameTest();
protected:
	virtual void createScenes() override;
};
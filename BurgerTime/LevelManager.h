#pragma once
#include "Game.h"
#include <vector>

class LevelManager {
	Game* game;
	Engine* engine;

public:
	LevelManager(Game* game);

	void loadLevel(const char* levelPath);
};


#pragma once
#include "Game.h"
#include <vector>
#include <string>

class LevelManager {
	Game* game;
	Engine* engine;

public:
	LevelManager(Game* game);

	void loadLevel(const char* levelPath);
	std::string* promptLevel();

private:
	std::vector<std::string> listLevels();
};


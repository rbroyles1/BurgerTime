#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "LevelManager.h"
#include "RenderComponent.h"
#include "Sprite.h"
#include <cstdio>

LevelManager::LevelManager(Game * game) {
	this->game = game;
	this->engine = engine;
}

void LevelManager::loadLevel(const char* levelPath) {
	FILE *fp;
	char type[50];
	int position[2];
	int extra;

	fp = fopen(levelPath, "r");

	while (!feof(fp)) {
		fscanf(fp, "%s %d %d %d", type, position, position + 1, &extra);

		if (strcmp(type, "") != 0) {
			if (strcmp(type, "FLOOR") == 0) {
				this->game->createFloor(new Coordinate(position), extra);
			}
			else if (strcmp(type, "STAIR") == 0) {
				this->game->createStair(new Coordinate(position));
			}
		}
	}

	fclose(fp);
}

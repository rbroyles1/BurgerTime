#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "LevelManager.h"
#include "RenderComponent.h"
#include "Sprite.h"
#include "IngredientEntity.h"
#include "EnemyEntity.h"
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
				this->game->addFloor(new Coordinate(position), extra);
			}
			else if (strcmp(type, "STAIR") == 0) {
				this->game->addStair(new Coordinate(position));
			}
			else if (strcmp(type, "PLAYER") == 0) {
				this->game->addPlayer(new Coordinate(position));
			}
			else if (strcmp(type, "DISH") == 0) {
				this->game->addDish(new Coordinate(position));
			}
			else if (strcmp(type, "BREAD_BOTTOM") == 0) {
				this->game->addIngredient(new Coordinate(position), BREAD_BOTTOM);
			}
			else if (strcmp(type, "BREAD_TOP") == 0) {
				this->game->addIngredient(new Coordinate(position), BREAD_TOP);
			}
			else if (strcmp(type, "CHEESE") == 0) {
				this->game->addIngredient(new Coordinate(position), CHEESE);
			}
			else if (strcmp(type, "LETTUCE") == 0) {
				this->game->addIngredient(new Coordinate(position), LETTUCE);
			}
			else if (strcmp(type, "MEAT") == 0) {
				this->game->addIngredient(new Coordinate(position), MEAT);
			}
			else if (strcmp(type, "TOMATO") == 0) {
				this->game->addIngredient(new Coordinate(position), TOMATO);
			}
			else if (strcmp(type, "SAUSAGE") == 0) {
				this->game->addEnemy(new Coordinate(position), SAUSAGE, extra / 1000.0);
			}
			else if (strcmp(type, "EGG") == 0) {
				this->game->addEnemy(new Coordinate(position), EGG, extra / 1000.0);
			}
			else if (strcmp(type, "CUCUMBER") == 0) {
				this->game->addEnemy(new Coordinate(position), CUCUMBER, extra / 1000.0);
			}
		}
	}

	fclose(fp);
}

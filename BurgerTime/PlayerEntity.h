#pragma once
#include "Entity.h"
#include "EnemyEntity.h"

class Game;

class PlayerEntity : public Entity {
	Game* game;
	Coordinate* initialPosition;
	CharacterAction action;
	CharacterAction lastDirection;
	Entity* pepper;
	bool pepperActive;
	double pepperActiveTime;

public:
	PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* enemies, Game* game);

	virtual void update(double dt);
	void setInitialPosition(Coordinate* position);
	void respawn();

	CharacterAction getAction();
	Entity* getPepper();

private:
	void createPepper();
	void throwPepper();
	void hidePepper();
};


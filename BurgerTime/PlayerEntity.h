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
	int pepperActiveMillisecs;

public:
	PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* enemies, Game* game);

	virtual void update(double dt);
	void setInitialPosition(Coordinate* position);
	void reset();

	CharacterAction getAction();
	Entity* getPepper();

private:
	void createPepper();
	void throwPepper();
	void hidePepper();
};


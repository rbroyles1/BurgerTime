#pragma once
#include "Entity.h"
#include "EnemyEntity.h"


class PlayerEntity : public Entity {
	CharacterAction action;
	Coordinate* initialPosition;

public:
	PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* enemies);

	virtual void update(double dt);
	void setInitialPosition(Coordinate* position);
	void reset();

	CharacterAction getAction();
};


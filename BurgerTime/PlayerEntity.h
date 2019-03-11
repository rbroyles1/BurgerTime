#pragma once
#include "Entity.h"
#include "EnemyEntity.h"

enum PlayerAction {WALK_LEFT, WALK_RIGHT, GO_UPSTAIRS, GO_DOWNSTAIRS, NO_ACTION, DIE, CELEBRATE_VICTORY};

class PlayerEntity : public Entity {
	PlayerAction action;
	Coordinate* initialPosition;

public:
	PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* enemies);

	virtual void update(double dt);
	void setInitialPosition(Coordinate* position);
	void reset();

	PlayerAction getAction();
};


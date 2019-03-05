#pragma once
#include "Entity.h"

enum PlayerAction {WALK_LEFT, WALK_RIGHT, NO_ACTION};

class PlayerEntity : public Entity {
	PlayerAction action;

public:
	PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* leftFloorsLimits, std::vector<Entity*>* rightFloorsLimits);

	virtual void update(double dt);

	PlayerAction getAction();
};


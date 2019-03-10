#pragma once
#include "Entity.h"

enum PlayerAction {WALK_LEFT, WALK_RIGHT, GO_UPSTAIRS, GO_DOWNSTAIRS, NO_ACTION, CELEBRATE_VICTORY};

class PlayerEntity : public Entity {
	PlayerAction action;

public:
	PlayerEntity(Engine* engine, Coordinate* position);

	void setPlayerColliders(std::vector<Entity*>* floors, std::vector<Entity*>* leftFloorsLimits, std::vector<Entity*>* rightFloorsLimits, 
		std::vector<Entity*>* stairs, std::vector<Entity*>* upStairsLimits, std::vector<Entity*>* downStairsLimits);

	virtual void update(double dt);

	PlayerAction getAction();
};


#pragma once
#include "Entity.h"
#include "Game.h"

class DishFakeFloorEntity : public Entity {

public:
	DishFakeFloorEntity(Engine* engine, Coordinate* position);

	virtual void receive(Message message);
};
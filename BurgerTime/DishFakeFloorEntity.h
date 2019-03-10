#pragma once
#include "Entity.h"
#include "Game.h"

class DishFakeFloorEntity : public Entity {
	Game* game;

public:
	DishFakeFloorEntity(Engine* engine, Coordinate* position, Game* game);

	virtual void receive(Message message);
};
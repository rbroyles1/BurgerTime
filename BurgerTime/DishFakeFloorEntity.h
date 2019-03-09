#pragma once
#include "Entity.h"

class DishFakeFloorEntity : public Entity {

public:
	DishFakeFloorEntity(Engine* engine, Coordinate* position);

	virtual void receive(Message message);
};
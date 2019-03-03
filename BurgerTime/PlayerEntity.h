#pragma once
#include "Entity.h"
#include "BoxCollideComponent.h"

class PlayerEntity : public Entity {

public:
	PlayerEntity(Engine* engine, Coordinate position);

	virtual void receive(Message message);

	~PlayerEntity();
};


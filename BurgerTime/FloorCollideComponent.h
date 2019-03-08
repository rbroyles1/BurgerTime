#pragma once
#include <vector>
#include "Component.h"
#include "Engine.h"

class FloorCollideComponent : public Component {
	Message message;
	std::vector<Entity*>* floors;
	Entity* additionalEntity;

public:
	FloorCollideComponent(Engine* engine, Entity* entity, Message message, std::vector<Entity*>* floors);
	FloorCollideComponent(Engine* engine, Entity* entity, Message message, std::vector<Entity*>* floors, Entity* additionalEntity);

	virtual void update(double dt);
};


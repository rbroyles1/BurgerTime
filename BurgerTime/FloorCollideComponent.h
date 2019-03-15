#pragma once
#include <vector>
#include "Component.h"
#include "Engine.h"

class FloorCollideComponent : public Component {
	Message message;
	std::vector<Entity*>* floors;
	Entity* additionalEntity;
	bool isPlayer;

public:
	FloorCollideComponent(Engine* engine, Entity* entity, Message message, std::vector<Entity*>* floors, bool isPlayer);
	FloorCollideComponent(Engine* engine, Entity* entity, Message message, std::vector<Entity*>* floors, bool isPlayer, Entity* additionalEntity);

	virtual void update(double dt);
};


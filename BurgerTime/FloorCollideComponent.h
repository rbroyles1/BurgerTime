#pragma once
#include <vector>
#include "Component.h"
#include "Engine.h"

class FloorCollideComponent : public Component {
	std::vector<Entity*>* floors;

public:
	FloorCollideComponent(Engine* engine, Entity* entity, std::vector<Entity*>* floors);

	virtual void update(double dt);
};


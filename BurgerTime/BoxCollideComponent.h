#pragma once
#include "Engine.h"
#include "Coordinate.h"
#include "Component.h"
#include <vector>

class Component;

class BoxCollideComponent : public Component {
	std::vector<Entity*>* colliders;
	Message message;

public:
	BoxCollideComponent(Engine* engine, Entity* entity, Message message, std::vector<Entity*>* potentialColliders);

	virtual void update(double dt);
};
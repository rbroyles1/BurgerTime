#pragma once
#include "Engine.h"
#include "Coordinate.h"
#include "Component.h"
#include <vector>

class Component;

class BoxCollideComponent : public Component {
	std::vector<BoxCollideComponent*>* colliders;
	Coordinate* boxSize;
	Message message;

public:
	BoxCollideComponent(Engine* engine, Entity* entity, Coordinate* boxSize, Message message, std::vector<BoxCollideComponent*>* colliders);

	virtual void update(double dt);
};
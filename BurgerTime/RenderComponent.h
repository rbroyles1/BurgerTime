#pragma once
#include "Component.h"
#include "Sprite.h"

class RenderComponent : public Component {
	Sprite* sprite;
	Coordinate* offset;

public:
	RenderComponent(Engine* engine, Entity* entity, Sprite* sprite);
	RenderComponent(Engine* engine, Entity* entity, Sprite* sprite, Coordinate* offset);

	virtual void update(double dt);

	~RenderComponent();
};


#pragma once
#include "Component.h"
#include "Sprite.h"

class RenderComponent : public Component {
	Sprite* sprite;

public:
	RenderComponent(Engine* engine, Entity* entity, Sprite* sprite);

	virtual void update(float dt);
};


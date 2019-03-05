#pragma once
#include "Component.h"
#include "Sprite.h"

class PlayerRenderComponent : public Component {
	Sprite* standingStill;
	Sprite* walkingLeft;
	Sprite* walkingRight;

public:
	PlayerRenderComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);

	~PlayerRenderComponent();
};


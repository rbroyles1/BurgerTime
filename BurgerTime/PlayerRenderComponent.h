#pragma once
#include "Component.h"
#include "Sprite.h"

class PlayerRenderComponent : public Component {
	Message lastReceived;

	Sprite* standingStill;
	Sprite* walkingLeft;
	Sprite* walkingRight;

	bool canWalk;

public:
	PlayerRenderComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);
	virtual void receive(Message message);

	~PlayerRenderComponent();
};


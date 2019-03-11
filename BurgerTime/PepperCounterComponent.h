#pragma once
#include "Component.h"
#include "Text.h"
#include "Game.h"

class PepperCounterComponent : public Component {
	Text* header;
	Text* pepper;
	Game* game;

public:
	PepperCounterComponent(Engine* engine, Entity* entity, Game* game);

	virtual void update(double dt);

	~PepperCounterComponent();
};


#pragma once
#include "Component.h"
#include "Text.h"
#include "Game.h"

class ScoreCounterComponent : public Component {
	Text* header;
	Text* score;
	Game* game;

public:
	ScoreCounterComponent(Engine* engine, Entity* entity, Game* game);

	virtual void update(double dt);

	~ScoreCounterComponent();
};


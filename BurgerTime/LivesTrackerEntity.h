#pragma once
#include "Entity.h"
#include "Game.h"
#include "RenderComponent.h"
#include <vector>

class LivesTrackerEntity : public Entity {
	Game* game;
	std::vector<RenderComponent*>* sprites;

public:
	LivesTrackerEntity(Engine* engine, Coordinate* position, Game* game);

	virtual void update(double dt);
};


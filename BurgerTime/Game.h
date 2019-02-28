#pragma once
#include <vector>
#include "Entity.h"

class Engine;
class Entity;

class Game : public Entity {
	Engine* engine;
	std::vector<Entity*>* entities;

public:

	Game(Engine* engine);

	virtual void init();
	virtual void update(float dt);
	void addEntity(Entity* entity);
	
	virtual ~Game();

private:
	void createFpsCounter();
};
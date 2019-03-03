#pragma once
#include <vector>
#include "BoxCollideComponent.h"
#include "Entity.h"

class Engine;
class Entity;
class BoxCollideComponent;

class Game : public Entity {
	std::vector<Entity*>* entities;
	std::vector<BoxCollideComponent*>* colliders;

public:

	Game(Engine* engine);

	virtual void init();
	virtual void update(double dt);
	virtual void receive(Message message);
	void addEntity(Entity* entity);
	
	virtual ~Game();

private:
	void createGameComponents();
	void createFpsCounter();
	void createPlayerEntity();
};
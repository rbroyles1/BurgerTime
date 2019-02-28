#pragma once
#include <vector>
#include "Entity.h"
#include "FpsCounterComponent.h"
#include "Text.h"

class Game : public Entity {
	Engine* engine;
	std::vector<Entity*>* entities;

public:
	SDL_Renderer* renderer;

	Game(Engine* engine, SDL_Renderer* renderer) {
		this->engine = engine;
		this->entities = new std::vector<Entity*>();
		this->renderer = renderer;
	}

	virtual void init() {
		this->createFpsCounter();

		Entity::init();
	}

	virtual void update(float dt) {
		Entity::update(dt);

		for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
			(*it)->update(dt);
		}
	}

	void addEntity(Entity* entity) {
		this->entities->push_back(entity);
	}

	virtual ~Game() {
		Entity::~Entity();

		for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
			delete *it;
		}

		delete this->entities;
	}

private:
	void createFpsCounter() {
		Entity* fpsCounter = new Entity(Coordinate(20, 20));
		Text* text = new Text(this->renderer, "space_invaders.ttf", 25);

		fpsCounter->addComponent(new FpsCounterComponent(this->engine, fpsCounter, text));
		this->addEntity(fpsCounter);
	}
};
#pragma once
#include <vector>
#include "Component.h"
#include "Coordinate.h"

enum Message { HIT };

class Entity {

protected:
	unsigned int id;
	Coordinate* position;

	std::vector<Component*>* components;
	std::vector<Entity*>* receivers;

public:

	Entity(Coordinate position) {
		this->id = 0;
		this->position = new Coordinate();
		this->components = new std::vector<Component*>();
		this->receivers = new std::vector<Entity*>();

		this->position->x = position.x;
		this->position->y = position.y;
	}

	Entity() : Entity(Coordinate(0, 0)) {}

	virtual void init() {
		for (auto it = this->components->begin(); it != this->components->end(); it++) {
			(*it)->init();
		}
	}

	virtual void update(float dt) {
		for (auto it = this->components->begin(); it != this->components->end(); it++) {
			(*it)->update(dt);
		}
	}

	virtual void addComponent(Component* component) {
		this->components->push_back(component);
	}

	virtual void addReceiver(Entity *entity) {
		this->receivers->push_back(entity);
	}

	virtual void send(Message message) {
		for (auto it = this->receivers->begin(); it != this->receivers->end(); it++) {
			(*it)->receive(message);
		}
	}

	virtual void receive(Message message) { }

	virtual ~Entity() {
		for (auto it = this->components->begin(); it != this->components->end(); it++) {
			delete *it;
		}

		for (auto it = this->receivers->begin(); it != this->receivers->end(); it++) {
			delete *it;
		}

		delete this->position;
		delete this->components;
		delete this->receivers;
	}

	Coordinate* getPosition() {
		return this->position;
	}

	void setPosition(Coordinate& position) {
		this->position->x = position.x;
		this->position->y = position.y;
	}
};
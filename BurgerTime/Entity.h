#pragma once
#include <vector>
#include "Component.h"
#include "Coordinate.h"

using std::vector;

enum Message {  };

class Entity {
	static int nextId;

protected:
	unsigned int id;
	Coordinate* position;

	vector<Component*>* components;
	vector<Entity*>* receivers;

public:
	Entity() {
		this->id = ++nextId;
		this->position = new Coordinate();
		this->components = new vector<Component*>();
		this->receivers = new vector<Entity*>();
	}

	virtual void init(Coordinate& position) {
		this->position->x = position.x;
		this->position->y = position.y;

		for (auto it = this->components->begin(); it != this->components->end(); it++) {
			(*it)->init();
		}
	}

	virtual void update(float dt) {
		for (auto it = this->components->begin(); it != this->components->end(); it++) {
			(*it)->update(dt);
		}
	}

	virtual void addReceiver(Entity *entity) {
		this->receivers->push_back(entity);
	}

	virtual void send(Message message) {
		for (auto it = this->receivers->begin(); it != this->receivers->end(); it++) {
			(*it)->receive(message);
		}
	}

	virtual void receive(Message message) {}

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
};

int Entity::nextId = 0;
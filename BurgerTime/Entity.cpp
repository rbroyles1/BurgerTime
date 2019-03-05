#include "Entity.h"

Entity::Entity(Engine* engine, Coordinate position) {
	this->id = 0;
	this->engine = engine;
	this->position = new Coordinate();
	this->components = new std::vector<Component*>();

	this->position->copyFrom(position);
}

Entity::Entity(Engine* engine) : Entity(engine, Coordinate(0, 0)) {}

void Entity::init() {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		(*it)->init();
	}
}

void Entity::update(double dt) {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		(*it)->update(dt);
	}
}

void Entity::addComponent(Component* component) {
	this->components->push_back(component);
}

void Entity::receive(Message message) { }

Coordinate* Entity::getPosition() {
	return this->position;
}

void Entity::setPosition(Coordinate& position) {
	this->position->copyFrom(position);
}

Entity::~Entity() {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		delete *it;
	}

	delete this->position;
	delete this->components;
}
#include "Entity.h"

Entity::Entity(Engine* engine, Coordinate* position) {
	this->engine = engine;
	this->position = position;
	this->components = new std::vector<Component*>();
	this->boundingBox = nullptr;
	this->enabled = true;
}

Entity::Entity(Engine* engine) : Entity(engine, new Coordinate(0, 0)) {}

void Entity::init() {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		(*it)->init();
	}
}

void Entity::update(double dt) {
	if (this->enabled) {
		for (auto it = this->components->begin(); it != this->components->end(); it++) {
			(*it)->update(dt);
		}
	}
}

void Entity::addComponent(Component* component) {
	this->components->push_back(component);
}

Component * Entity::getComponent(int index) {
	return this->components->at(index);
}

Coordinate* Entity::getPosition() {
	return this->position;
}

void Entity::setPosition(Coordinate& position) {
	this->position->copyFrom(position);
}

BoundingBox * Entity::getBoundingBox() {
	return this->boundingBox;
}

void Entity::setBoundingBox(BoundingBox * boundingBox) {
	this->boundingBox = boundingBox;
}

bool Entity::getEnabled() {
	return this->enabled;
}

void Entity::setEnabled(bool enabled) {
	this->enabled = enabled;
}

Entity::~Entity() {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		delete *it;
	}

	delete this->components;
	delete this->boundingBox;
}
#include "Entity.h"

Entity::Entity(Coordinate position) {
	this->id = 0;
	this->position = new Coordinate();
	this->components = new std::vector<Component*>();
	this->receivers = new std::vector<Entity*>();

	this->position->x = position.x;
	this->position->y = position.y;
}

Entity::Entity() : Entity(Coordinate(0, 0)) {}

void Entity::init() {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		(*it)->init();
	}
}

void Entity::update(float dt) {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		(*it)->update(dt);
	}
}

void Entity::addComponent(Component* component) {
	this->components->push_back(component);
}

void Entity::addReceiver(Entity *entity) {
	this->receivers->push_back(entity);
}

void Entity::send(Message message) {
	for (auto it = this->receivers->begin(); it != this->receivers->end(); it++) {
		(*it)->receive(message);
	}
}

Coordinate* Entity::getPosition() {
	return this->position;
}

void Entity::setPosition(Coordinate& position) {
	this->position->x = position.x;
	this->position->y = position.y;
}

void Entity::receive(Message message) { }

Entity::~Entity() {
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
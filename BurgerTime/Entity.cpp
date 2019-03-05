#include "Entity.h"

Entity::Entity(Engine* engine, Coordinate* position) {
	this->engine = engine;
	this->position = position;
	this->components = new std::vector<Component*>();
	this->receivedMessages = new std::unordered_set<Message>();
	this->boundingBox = nullptr;
}

Entity::Entity(Engine* engine) : Entity(engine, new Coordinate(0, 0)) {}

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

void Entity::receive(Message message) {
	this->receivedMessages->insert(message);
}

bool Entity::hasReceived(Message message) {
	return this->receivedMessages->count(message) > 0;
}

void Entity::clearMessages() {
	this->receivedMessages->clear();
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

Entity::~Entity() {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		delete *it;
	}

	delete this->position;
	delete this->components;
	delete this->boundingBox;
	delete this->receivedMessages;
}
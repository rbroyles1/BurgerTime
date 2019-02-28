#include "Component.h"

Component::Component(Engine* engine, Entity* entity) {
	this->engine = engine;
	this->entity = entity;
}

void Component::init() { }
void Component::update(float dt) { }
void Component::receive(Message message) { }

Component::~Component() { }
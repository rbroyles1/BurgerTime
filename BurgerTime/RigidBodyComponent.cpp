#include "RigidBodyComponent.h"
#include "Engine.h"

RigidBodyComponent::RigidBodyComponent(Engine * engine, Entity * entity) : Component(engine, entity) {
	this->velocity = new Coordinate();

	engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
}

void RigidBodyComponent::update(double dt) {
	Coordinate newPosition = *entity->getPosition() + *this->velocity * dt;
	entity->setPosition(newPosition);
}

RigidBodyComponent::~RigidBodyComponent() {
	delete this->velocity;
}

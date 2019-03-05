#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(Engine * engine, Entity * entity) : Component(engine, entity) {
	this->velocity = new Coordinate();
}

void RigidBodyComponent::update(double dt) {
	Coordinate newPosition = *entity->getPosition() + *this->velocity * dt;
	entity->setPosition(newPosition);
}

RigidBodyComponent::~RigidBodyComponent() {
	delete this->velocity;
}

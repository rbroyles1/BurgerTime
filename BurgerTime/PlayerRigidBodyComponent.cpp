#include "PlayerRigidBodyComponent.h"
#include "Constants.h"

PlayerRigidBodyComponent::PlayerRigidBodyComponent(Engine * engine, Entity * entity) : RigidBodyComponent(engine, entity) { }

void PlayerRigidBodyComponent::receive(Message message) {
	if (message == MOVE_LEFT) this->velocity->setX(-PLAYER_HORIZONTAL_VELOCITY);
	if (message == MOVE_RIGHT) this->velocity->setX(PLAYER_HORIZONTAL_VELOCITY);
}

void PlayerRigidBodyComponent::update(double dt) {
	RigidBodyComponent::update(dt);

	this->velocity->setX(0);
	this->velocity->setY(0);
}
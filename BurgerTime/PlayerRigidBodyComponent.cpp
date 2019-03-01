#include "PlayerRigidBodyComponent.h"
#include "Constants.h"

PlayerRigidBodyComponent::PlayerRigidBodyComponent(Engine * engine, Entity * entity) : RigidBodyComponent(engine, entity) { }

void PlayerRigidBodyComponent::receive(Message message) {
	if (message == MOVE_LEFT) velocity->x = -PLAYER_HORIZONTAL_VELOCITY * RESOLUTION_MULTIPLIER;
	if (message == MOVE_RIGHT) velocity->x = PLAYER_HORIZONTAL_VELOCITY * RESOLUTION_MULTIPLIER;
}

void PlayerRigidBodyComponent::update(double dt) {
	RigidBodyComponent::update(dt);
	this->velocity->x = this->velocity->y = 0;
}
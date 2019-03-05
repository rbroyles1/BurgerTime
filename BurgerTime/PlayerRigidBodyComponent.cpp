#include "PlayerRigidBodyComponent.h"
#include "Engine.h"
#include "Constants.h"

PlayerRigidBodyComponent::PlayerRigidBodyComponent(Engine * engine, Entity * entity) : RigidBodyComponent(engine, entity) {
	this->canWalkLeft = this->canWalkRight = true;

	engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
	engine->getMessageDispatcher()->subscribe(LIMIT_LEFT, this);
	engine->getMessageDispatcher()->subscribe(LIMIT_RIGHT, this);
}

void PlayerRigidBodyComponent::receive(Message message) {
	if (message == MOVE_LEFT) this->velocity->setX(-PLAYER_HORIZONTAL_VELOCITY);
	if (message == MOVE_RIGHT) this->velocity->setX(PLAYER_HORIZONTAL_VELOCITY);
	if (message == LIMIT_LEFT) this->canWalkLeft = false;
	if (message == LIMIT_RIGHT) this->canWalkRight = false;
}

void PlayerRigidBodyComponent::update(double dt) {
	if(!this->canWalkLeft && this->velocity->getX() < 0) this->velocity->setX(0);
	if(!this->canWalkRight && this->velocity->getX() > 0) this->velocity->setX(0);
	
	RigidBodyComponent::update(dt);

	this->velocity->setX(0);
	this->velocity->setY(0);
	this->canWalkLeft = this->canWalkRight = true;
}
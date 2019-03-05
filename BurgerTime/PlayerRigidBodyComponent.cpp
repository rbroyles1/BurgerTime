#include "PlayerRigidBodyComponent.h"
#include "PlayerEntity.h"
#include "Engine.h"
#include "Constants.h"

PlayerRigidBodyComponent::PlayerRigidBodyComponent(Engine * engine, Entity * entity) : RigidBodyComponent(engine, entity) { }

void PlayerRigidBodyComponent::update(double dt) {
	switch (((PlayerEntity*)this->entity)->getAction()) {
		case WALK_LEFT:
			this->velocity->setX(-PLAYER_HORIZONTAL_VELOCITY);
			break;
		case WALK_RIGHT:
			this->velocity->setX(PLAYER_HORIZONTAL_VELOCITY);
			break;
		default:
			this->velocity->setX(0);
			this->velocity->setY(0);
			break;
	}
	
	RigidBodyComponent::update(dt);
}
#include "PlayerRigidBodyComponent.h"
#include "PlayerEntity.h"
#include "Engine.h"
#include "Constants.h"

PlayerRigidBodyComponent::PlayerRigidBodyComponent(Engine * engine, Entity * entity) : RigidBodyComponent(engine, entity) { }

void PlayerRigidBodyComponent::update(double dt) {
	this->velocity->setX(0);
	this->velocity->setY(0);

	switch (((PlayerEntity*)this->entity)->getAction()) {
		case WALK_LEFT:
			this->velocity->setX(-PLAYER_HORIZONTAL_VELOCITY);
			break;
		case WALK_RIGHT:
			this->velocity->setX(PLAYER_HORIZONTAL_VELOCITY);
			break;
		case GO_UPSTAIRS:
			this->velocity->setY(-PLAYER_VERTICAL_VELOCITY);
			break;
		case GO_DOWNSTAIRS:
			this->velocity->setY(PLAYER_VERTICAL_VELOCITY);
			break;
	}
	
	RigidBodyComponent::update(dt);
}
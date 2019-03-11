#include "WalkingRigidBodyComponent.h"
#include "PlayerEntity.h"
#include "Engine.h"
#include "Constants.h"

WalkingRigidBodyComponent::WalkingRigidBodyComponent(Engine * engine, Entity * entity, bool isPlayer) : RigidBodyComponent(engine, entity) {
	this->isPlayer = isPlayer;
}

void WalkingRigidBodyComponent::update(double dt) {
	CharacterAction action = NO_ACTION;
	
	this->velocity->setX(0);
	this->velocity->setY(0);

	if (this->isPlayer) {
		action = ((PlayerEntity*)this->entity)->getAction();
	}
	else {
		action = ((EnemyEntity*)this->entity)->getAction();
	}

	switch (action) {
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
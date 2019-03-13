#include "WalkingRigidBodyComponent.h"
#include "PlayerEntity.h"
#include "Engine.h"
#include "Constants.h"

WalkingRigidBodyComponent::WalkingRigidBodyComponent(Engine * engine, Entity * entity, bool isPlayer) : RigidBodyComponent(engine, entity) {
	this->isPlayer = isPlayer;
}

void WalkingRigidBodyComponent::update(double dt) {
	CharacterAction action = NO_ACTION;
	double speedCoeficient;
	
	this->velocity->setX(0);
	this->velocity->setY(0);

	if (this->isPlayer) {
		action = ((PlayerEntity*)this->entity)->getAction();
		speedCoeficient = 1;
	}
	else {
		action = ((EnemyEntity*)this->entity)->getAction();
		speedCoeficient = ENEMY_PLAYER_SPEED_PROPORTION;
	}

	switch (action) {
		case WALK_LEFT:
			this->velocity->setX(-PLAYER_HORIZONTAL_VELOCITY * speedCoeficient);
			break;
		case WALK_RIGHT:
			this->velocity->setX(PLAYER_HORIZONTAL_VELOCITY * speedCoeficient);
			break;
		case GO_UPSTAIRS:
			this->velocity->setY(-PLAYER_VERTICAL_VELOCITY * speedCoeficient);
			break;
		case GO_DOWNSTAIRS:
			this->velocity->setY(PLAYER_VERTICAL_VELOCITY * speedCoeficient);
			break;
	}
	
	RigidBodyComponent::update(dt);
}
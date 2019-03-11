#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"
#include "PlayerRigidBodyComponent.h"
#include "FloorCollideComponent.h"
#include "BoxCollideComponent.h"
#include "Engine.h"

PlayerEntity::PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* enemies) : Entity(engine, position) {
	PlayerRenderComponent* renderComponent = new PlayerRenderComponent(this->engine, this);
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, this);

	this->addComponent(renderComponent);
	this->addComponent(rigidBodyComponent);
	this->addComponent(new BoxCollideComponent(this->engine, this, ENEMY_ATTACK, enemies));

	this->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	
	this->action = NO_ACTION;
	this->initialPosition = new Coordinate(position->getX(), position->getY());

	this->engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_UP, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_DOWN, this);
	this->engine->getMessageDispatcher()->subscribe(GAME_VICTORY, this);
}

void PlayerEntity::update(double dt) {
	Entity::update(dt);

	if (this->action != CELEBRATE_VICTORY) {
		this->action = NO_ACTION;

		if (this->hasReceived(ON_FLOOR)) {
			if (this->hasReceived(MOVE_LEFT) && !this->hasReceived(INTERSECT_LIMIT_LEFT)) {
				this->action = WALK_LEFT;
			}
			else if (this->hasReceived(MOVE_RIGHT) && !this->hasReceived(INTERSECT_LIMIT_RIGHT)) {
				this->action = WALK_RIGHT;
			}
		}
		if (this->hasReceived(MOVE_UP) && this->hasReceived(INTERSECT_STAIRS) && !this->hasReceived(INTERSECT_UP_STAIRS)) {
			this->action = GO_UPSTAIRS;
		}
		if (this->hasReceived(MOVE_DOWN) && this->hasReceived(INTERSECT_STAIRS) && !this->hasReceived(INTERSECT_DOWN_STAIRS)) {
			this->action = GO_DOWNSTAIRS;
		}
		if (this->hasReceived(GAME_VICTORY)) {
			this->action = CELEBRATE_VICTORY;
		}
		if (this->hasReceived(ENEMY_ATTACK)) {
			this->action = DIE;
		}
	}

	this->clearMessages();
}

void PlayerEntity::setInitialPosition(Coordinate* position) {
	this->setPosition(*position);
	this->initialPosition->copyFrom(*position);
}

void PlayerEntity::reset() {
	this->action = NO_ACTION;
	this->setPosition(*this->initialPosition);
}

CharacterAction PlayerEntity::getAction() {
	return this->action;
}

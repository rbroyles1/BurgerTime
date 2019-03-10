#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"
#include "PlayerRigidBodyComponent.h"
#include "FloorCollideComponent.h"
#include "Engine.h"

PlayerEntity::PlayerEntity(Engine* engine, Coordinate* position) : Entity(engine, position) {
	PlayerRenderComponent* renderComponent = new PlayerRenderComponent(this->engine, this);
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, this);

	this->addComponent(renderComponent);
	this->addComponent(rigidBodyComponent);

	this->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	this->action = NO_ACTION;

	this->engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_UP, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_DOWN, this);
	this->engine->getMessageDispatcher()->subscribe(GAME_VICTORY, this);
}

void PlayerEntity::setPlayerColliders(std::vector<Entity*>* floors, std::vector<Entity*>* leftFloorsLimits, std::vector<Entity*>* rightFloorsLimits,
	std::vector<Entity*>* stairs, std::vector<Entity*>* upStairsLimits, std::vector<Entity*>* downStairsLimits) {
	
	FloorCollideComponent* floorBox = new FloorCollideComponent(this->engine, this, ON_FLOOR, floors);
	BoxCollideComponent* leftBox = new BoxCollideComponent(this->engine, this, INTERSECT_LIMIT_LEFT, leftFloorsLimits);
	BoxCollideComponent* rightBox = new BoxCollideComponent(this->engine, this, INTERSECT_LIMIT_RIGHT, rightFloorsLimits);
	BoxCollideComponent* stairsBox = new BoxCollideComponent(this->engine, this, INTERSECT_STAIRS, stairs);
	BoxCollideComponent* upStairsBox = new BoxCollideComponent(this->engine, this, INTERSECT_UP_STAIRS, upStairsLimits);
	BoxCollideComponent* downStairsBox = new BoxCollideComponent(this->engine, this, INTERSECT_DOWN_STAIRS, downStairsLimits);

	this->addComponent(floorBox);
	this->addComponent(leftBox);
	this->addComponent(rightBox);
	this->addComponent(stairsBox);
	this->addComponent(upStairsBox);
	this->addComponent(downStairsBox);
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
	}

	this->clearMessages();
}

PlayerAction PlayerEntity::getAction() {
	return this->action;
}

#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"
#include "PlayerRigidBodyComponent.h"
#include "Engine.h"

PlayerEntity::PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* leftFloorsLimits, std::vector<Entity*>* rightFloorsLimits) : Entity(engine, position) {
	PlayerRenderComponent* renderComponent = new PlayerRenderComponent(this->engine, this);
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, this);
	BoxCollideComponent* playerBoxLeft = new BoxCollideComponent(this->engine, this, LIMIT_LEFT, leftFloorsLimits);
	BoxCollideComponent* playerBoxRight = new BoxCollideComponent(this->engine, this, LIMIT_RIGHT, rightFloorsLimits);

	this->addComponent(renderComponent);
	this->addComponent(rigidBodyComponent);
	this->addComponent(playerBoxLeft);
	this->addComponent(playerBoxRight);

	this->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));

	this->engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
}

void PlayerEntity::update(double dt) {
	Entity::update(dt);
	this->action = NO_ACTION;

	if (this->hasReceived(MOVE_LEFT) && !this->hasReceived(LIMIT_LEFT)) {
		this->action = WALK_LEFT;
	}
	else if (this->hasReceived(MOVE_RIGHT) && !this->hasReceived(LIMIT_RIGHT)) {
		this->action = WALK_RIGHT;
	}

	this->clearMessages();
}

PlayerAction PlayerEntity::getAction() {
	return this->action;
}

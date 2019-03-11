#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"
#include "PlayerRigidBodyComponent.h"
#include "FloorCollideComponent.h"
#include "BoxCollideComponent.h"
#include "RenderComponent.h"
#include "Engine.h"

PlayerEntity::PlayerEntity(Engine* engine, Coordinate* position, std::vector<Entity*>* enemies, Game* game) : Entity(engine, position) {
	this->game = game;
	
	PlayerRenderComponent* renderComponent = new PlayerRenderComponent(this->engine, this);
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, this);

	this->addComponent(renderComponent);
	this->addComponent(rigidBodyComponent);
	this->addComponent(new BoxCollideComponent(this->engine, this, ENEMY_ATTACK, enemies));

	this->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	
	this->action = NO_ACTION;
	this->lastDirection = WALK_LEFT;
	this->initialPosition = new Coordinate(position->getX(), position->getY());

	this->createPepper();

	this->engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_UP, this);
	this->engine->getMessageDispatcher()->subscribe(MOVE_DOWN, this);
	this->engine->getMessageDispatcher()->subscribe(MAIN_ACTION, this);
	this->engine->getMessageDispatcher()->subscribe(GAME_VICTORY, this);
}

void PlayerEntity::update(double dt) {
	Entity::update(dt);

	if (this->action != CELEBRATE_VICTORY) {
		this->action = NO_ACTION;

		if (this->hasReceived(ON_FLOOR)) {
			if (this->hasReceived(MOVE_LEFT) && !this->hasReceived(INTERSECT_LIMIT_LEFT)) {
				this->action = this->lastDirection = WALK_LEFT;
			}
			else if (this->hasReceived(MOVE_RIGHT) && !this->hasReceived(INTERSECT_LIMIT_RIGHT)) {
				this->action = this->lastDirection = WALK_RIGHT;
			}
		}
		if (this->hasReceived(MOVE_UP) && this->hasReceived(INTERSECT_STAIRS) && !this->hasReceived(INTERSECT_UP_STAIRS)) {
			this->action = GO_UPSTAIRS;
		}
		if (this->hasReceived(MOVE_DOWN) && this->hasReceived(INTERSECT_STAIRS) && !this->hasReceived(INTERSECT_DOWN_STAIRS)) {
			this->action = GO_DOWNSTAIRS;
		}
		if (this->hasReceived(MAIN_ACTION)) {
			this->throwPepper();
		}
		if (this->hasReceived(GAME_VICTORY)) {
			this->action = CELEBRATE_VICTORY;
		}
		if (this->hasReceived(ENEMY_ATTACK)) {
			this->action = DIE;
		}
	}

	if (this->pepperActive) {
		this->pepperActiveMillisecs += dt * 1000;

		if (this->pepperActiveMillisecs >= PEPPER_ANIMATION_MILLISECS * 4) {
			this->hidePepper();
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

Entity* PlayerEntity::getPepper() {
	return this->pepper;
}

void PlayerEntity::createPepper() {
	this->pepper = new Entity(this->engine);
	this->hidePepper();

	Sprite* pepperSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/pepper (%d).bmp", 1, 4, PEPPER_ANIMATION_MILLISECS);

	this->pepper->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	this->pepper->addComponent(new RenderComponent(this->engine, this->pepper, pepperSprite));
}

void PlayerEntity::throwPepper() {
	if (!this->pepperActive && this->game->getPepper() > 0) {
		int pepperOffset = this->lastDirection == WALK_LEFT ? -16 : 16;
		Coordinate pepperPos = Coordinate(this->position->getX() + pepperOffset, this->position->getY());

		((RenderComponent*)this->pepper->getComponent(0))->getSprite()->resetAnimation();
		
		this->pepper->setPosition(pepperPos);
		this->pepperActive = true;
		this->engine->getMessageDispatcher()->send(PEPPER_THROWN);
	}
}

void PlayerEntity::hidePepper() {
	Coordinate newPos = Coordinate(900, 900);

	this->pepperActive = false;
	this->pepperActiveMillisecs = 0;
	this->pepper->setPosition(newPos);
}

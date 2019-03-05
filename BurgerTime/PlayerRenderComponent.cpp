#include "Engine.h"
#include "PlayerRenderComponent.h"

PlayerRenderComponent::PlayerRenderComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->standingStill = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_downstairs (2).bmp");
	this->walkingLeft = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_left (%d).bmp", 1, 3);
	this->walkingRight = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_right (%d).bmp", 1, 3);

	this->lastReceived = NULL_MESSAGE;
	this->canWalk = true;

	engine->getMessageDispatcher()->subscribe(MOVE_LEFT, this);
	engine->getMessageDispatcher()->subscribe(MOVE_RIGHT, this);
	engine->getMessageDispatcher()->subscribe(LIMIT_LEFT, this);
	engine->getMessageDispatcher()->subscribe(LIMIT_RIGHT, this);
}

void PlayerRenderComponent::update(double dt) {
	Sprite* sprite = nullptr;

	if (this->lastReceived == MOVE_LEFT && this->canWalk) {
		sprite = this->walkingLeft;
		this->walkingRight->resetAnimation();
	}
	else if (this->lastReceived == MOVE_RIGHT && this->canWalk) {
		sprite = this->walkingRight;
		this->walkingLeft->resetAnimation();
	}
	else {
		sprite = this->standingStill;
		this->walkingLeft->resetAnimation();
		this->walkingRight->resetAnimation();
	}

	sprite->draw(entity->getPosition()->getX(), entity->getPosition()->getY(), dt);
	
	this->lastReceived = NULL_MESSAGE;
	this->canWalk = true;
}

void PlayerRenderComponent::receive(Message message) {
	if (message == MOVE_LEFT || message == MOVE_RIGHT) {
		this->lastReceived = message;
	}
	else if (message == LIMIT_LEFT || message == LIMIT_RIGHT) {
		this->canWalk = false;
	}
}

PlayerRenderComponent::~PlayerRenderComponent() {
	delete this->standingStill;
	delete this->walkingLeft;
	delete this->walkingRight;
}

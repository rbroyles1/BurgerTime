#include "Engine.h"
#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"

PlayerRenderComponent::PlayerRenderComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->standingStill = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_downstairs (2).bmp");
	this->walkingLeft = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_left (%d).bmp", 1, 3);
	this->walkingRight = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_right (%d).bmp", 1, 3);
}

void PlayerRenderComponent::update(double dt) {
	Sprite* sprite = nullptr;

	switch (((PlayerEntity*)this->entity)->getAction()) {
		case WALK_LEFT:
			sprite = this->walkingLeft;
			this->walkingRight->resetAnimation();
			break;
		case WALK_RIGHT:
			sprite = this->walkingRight;
			this->walkingLeft->resetAnimation();
			break;
		default:
			sprite = this->standingStill;
			this->walkingLeft->resetAnimation();
			this->walkingRight->resetAnimation();
			break;
	}

	sprite->draw(entity->getPosition()->getX(), entity->getPosition()->getY(), dt);
}

PlayerRenderComponent::~PlayerRenderComponent() {
	delete this->standingStill;
	delete this->walkingLeft;
	delete this->walkingRight;
}

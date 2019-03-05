#include "Engine.h"
#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"

PlayerRenderComponent::PlayerRenderComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->standingStill = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_downstairs (2).bmp");
	this->walkingLeft = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_left (%d).bmp", 1, 3, WALKING_ANIMATION_MILLISECS);
	this->walkingRight = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_right (%d).bmp", 1, 3, WALKING_ANIMATION_MILLISECS);
	this->upStairs = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_upstairs (%d).bmp", 1, 3, STAIRS_ANIMATION_MILLISECS);
	this->downStairs = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_downstairs (%d).bmp", 1, 3, STAIRS_ANIMATION_MILLISECS);
}

void PlayerRenderComponent::update(double dt) {
	Sprite* sprite = nullptr;

	switch (((PlayerEntity*)this->entity)->getAction()) {
		case WALK_LEFT:
			sprite = this->walkingLeft;
			break;
		case WALK_RIGHT:
			sprite = this->walkingRight;
			break;
		case GO_UPSTAIRS:
			sprite = this->upStairs;
			break;
		case GO_DOWNSTAIRS:
			sprite = this->downStairs;
			break;
		default:
			sprite = this->standingStill;
			break;
	}

	sprite->draw(entity->getPosition()->getX(), entity->getPosition()->getY(), dt);
}

PlayerRenderComponent::~PlayerRenderComponent() {
	delete this->standingStill;
	delete this->walkingLeft;
	delete this->walkingRight;
	delete this->upStairs;
	delete this->downStairs;
}

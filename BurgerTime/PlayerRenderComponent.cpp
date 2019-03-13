#include "Engine.h"
#include "PlayerEntity.h"
#include "PlayerRenderComponent.h"

PlayerRenderComponent::PlayerRenderComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->standingStill = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_downstairs (2).bmp");
	this->walkingLeft = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_left (%d).bmp", 1, 3, WALKING_ANIMATION_MILLISECS);
	this->walkingRight = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_right (%d).bmp", 1, 3, WALKING_ANIMATION_MILLISECS);
	this->upStairs = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_upstairs (%d).bmp", 1, 3, STAIRS_ANIMATION_MILLISECS);
	this->downStairs = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_downstairs (%d).bmp", 1, 3, STAIRS_ANIMATION_MILLISECS);
	this->celebrate = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_celebrate (%d).bmp", 1, 2, COOK_CELEBRATE_ANIMATION_MILLISECS);
	this->die1 = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_die1 (%d).bmp", 1, 3, COOK_DIE_ANIMATION_MILLISECS);
	this->die2 = new Sprite(this->engine->getRenderer(), "resources/sprites/cook_die2 (%d).bmp", 1, 2, COOK_DIE_ANIMATION_MILLISECS);

	this->deadTime = 0;
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
		case CELEBRATE_VICTORY:
			sprite = this->celebrate;
			break;
		case DIE:
			sprite = this->die1;
			this->deadTime += dt;

			if (this->deadTime * 1000 >= COOK_DIE_ANIMATION_MILLISECS * 3) {
				sprite = this->die2;

				if (this->deadTime * 1000 >= COOK_DIE_ANIMATION_MILLISECS * 16) {
					this->engine->getMessageDispatcher()->send(PLAYER_DIED);

					if (((PlayerEntity*)this->entity)->getAction() == NO_ACTION) {
						this->deadTime = 0;
					}
				}
			}
			break;
		default:
			sprite = this->standingStill;
			break;
	}

	sprite->draw((int)entity->getPosition()->getX(), (int)entity->getPosition()->getY(), dt);
}

PlayerRenderComponent::~PlayerRenderComponent() {
	delete this->standingStill;
	delete this->walkingLeft;
	delete this->walkingRight;
	delete this->upStairs;
	delete this->downStairs;
}

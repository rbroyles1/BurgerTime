#include "EnemyRenderComponent.h"
#include "Engine.h"
#include <string>

EnemyRenderComponent::EnemyRenderComponent(Engine* engine, Entity* entity, EnemyType enemyType) : Component(engine, entity) {
	char enemyPattern[200];

	this->deadMillisecs = this->stunnedMillisecs = 0;

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_left (%%d).bmp", enemyType);
	this->walkingLeft = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);
	
	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_right (%%d).bmp", enemyType);
	this->walkingRight = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_upstairs (%%d).bmp", enemyType);
	this->upStairs = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_downstairs (%%d).bmp", enemyType);
	this->downStairs = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_squashed (%%d).bmp", enemyType);
	this->squashed = new Sprite(engine->getRenderer(), enemyPattern, 1, 4, ENEMY_SQUASHED_ANIMATION_MILLISECS);

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_stunned (%%d).bmp", enemyType);
	this->stunned = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_STUNNED_ANIMATION_MILLISECS);
}

void EnemyRenderComponent::update(double dt) {
	Sprite* sprite = nullptr;
	
	switch (((EnemyEntity*)this->entity)->getAction()) {
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
		case STUNNED:
			sprite = this->stunned;
			this->stunnedMillisecs += dt * 1000;

			if (this->stunnedMillisecs >= ENEMY_STUNNED_ANIMATION_MILLISECS * 16) {
				this->stunnedMillisecs = 0;
				this->entity->receive(ENEMY_UNPEPPERED);
			}
			break;
		case DIE:
			sprite = this->squashed;
			this->deadMillisecs += dt * 1000;

			if (this->deadMillisecs >= ENEMY_SQUASHED_ANIMATION_MILLISECS * 4) {
				this->entity->setEnabled(false);
				this->deadMillisecs = 0;
				this->stunnedMillisecs = 0;
			}
			break;
		default:
			sprite = this->walkingLeft;
			break;
	}

	sprite->draw(this->entity->getPosition()->getX(), this->entity->getPosition()->getY(), dt);
}

void EnemyRenderComponent::writeSpritePattern(char* buffer, const char* prePattern, EnemyType enemyType) {
	switch (enemyType) {
		case SAUSAGE:
			snprintf(buffer, 200, prePattern, "sausage");
			break;
		case EGG:
			snprintf(buffer, 200, prePattern, "egg");
			break;
		case CUCUMBER:
			snprintf(buffer, 200, prePattern, "cucumber");
			break;
	}
}

EnemyRenderComponent::~EnemyRenderComponent() {
	delete this->walkingLeft;
	delete this->walkingRight;
	delete this->upStairs;
	delete this->downStairs;
	delete this->squashed;
}
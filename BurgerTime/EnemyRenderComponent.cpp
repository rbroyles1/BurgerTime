#include "EnemyRenderComponent.h"
#include "Engine.h"
#include <string>

EnemyRenderComponent::EnemyRenderComponent(Engine* engine, Entity* entity, EnemyType enemyType) : Component(engine, entity) {
	char enemyPattern[200];

	this->deadTime = this->stunnedTime = 0;

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

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_downstairs (1).bmp", enemyType);
	this->standStill = new Sprite(engine->getRenderer(), enemyPattern);
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
			this->stunnedTime += dt;

			if (this->stunnedTime * 1000 >= ENEMY_STUNNED_ANIMATION_MILLISECS * 16) {
				this->stunnedTime = 0;
				this->entity->receive(ENEMY_UNPEPPERED);
			}
			break;
		case DIE:
			sprite = this->squashed;
			this->deadTime += dt;

			if (this->deadTime * 1000 >= ENEMY_SQUASHED_ANIMATION_MILLISECS * 4) {
				this->entity->setEnabled(false);
				this->deadTime = 0;
				this->stunnedTime = 0;
			}
			break;
		default:
			sprite = this->standStill;
			break;
	}

	sprite->draw((int)this->entity->getPosition()->getX(), (int)this->entity->getPosition()->getY(), dt);
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
	delete this->stunned;
	delete this->standStill;
}
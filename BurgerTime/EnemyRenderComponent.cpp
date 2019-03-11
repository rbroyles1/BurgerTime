#include "EnemyRenderComponent.h"
#include "Engine.h"
#include <string>

EnemyRenderComponent::EnemyRenderComponent(Engine* engine, Entity* entity, EnemyType enemyType) : Component(engine, entity) {
	char enemyPattern[200];

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_left (%%d).bmp", enemyType);
	this->walkingLeft = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);
	
	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_right (%%d).bmp", enemyType);
	this->walkingRight = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_upstairs (%%d).bmp", enemyType);
	this->upStairs = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);

	this->writeSpritePattern(enemyPattern, "resources/sprites/%s_downstairs (%%d).bmp", enemyType);
	this->downStairs = new Sprite(engine->getRenderer(), enemyPattern, 1, 2, ENEMY_WALKING_ANIMATION_MILLISECS);
}

void EnemyRenderComponent::update(double dt) {
	this->walkingRight->draw(this->entity->getPosition()->getX(), this->entity->getPosition()->getY(), dt);
}

void EnemyRenderComponent::writeSpritePattern(char* buffer, const char* prePattern, EnemyType enemyType) {
	switch (enemyType) {
		case SAUSAGE:
			snprintf(buffer, 200, prePattern, "sausage");
			break;
	}
}

EnemyRenderComponent::~EnemyRenderComponent() {
	delete this->walkingLeft;
	delete this->walkingRight;
	delete this->upStairs;
	delete this->downStairs;
}
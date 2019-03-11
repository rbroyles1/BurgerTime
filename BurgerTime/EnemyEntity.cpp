#include "EnemyEntity.h"
#include "BoxCollideComponent.h"
#include "EnemyRenderComponent.h"
#include "EnemyIngredientCollideComponent.h"

EnemyEntity::EnemyEntity(Engine* engine, Coordinate* position, EnemyType enemyType, PlayerEntity* player, std::vector<Entity*>* ingredients) : Entity(engine, position) {
	this->initialPosition = new Coordinate(position->getX(), position->getY());
	this->action = WALK_LEFT;
	this->deadMillisecs = 0;

	std::vector<Entity*>* pepperVector = new std::vector<Entity*>();
	pepperVector->push_back(player->getPepper());
	
	this->setBoundingBox(new BoundingBox(new Coordinate(2, 2)));
	this->addComponent(new EnemyRenderComponent(engine, this, enemyType));
	this->addComponent(new BoxCollideComponent(engine, this, ENEMY_PEPPERED, pepperVector));
	this->addComponent(new EnemyIngredientCollideComponent(engine, this, ingredients));
}

void EnemyEntity::update(double dt) {
	Entity::update(dt);

	if (this->hasReceived(ENEMY_SQUASHED)) {
		this->action = DIE;
		this->engine->getMessageDispatcher()->send(ENEMY_SQUASHED);
	}
	if (this->hasReceived(ENEMY_PEPPERED) || this->action == STUNNED) {
		this->action = STUNNED;
	}
	if (this->hasReceived(ENEMY_UNPEPPERED)) {
		this->action = WALK_LEFT;
	}
	if (this->action == DIE) {
		this->deadMillisecs += dt * 1000;
		this->position->setY(300);

		if (this->deadMillisecs >= 2000) {
			this->respawn();
		}
	}

	this->clearMessages();
}

void EnemyEntity::reset() {
	this->setPosition(*this->initialPosition);
}

CharacterAction EnemyEntity::getAction() {
	return this->action;
}

void EnemyEntity::respawn() {
	this->setEnabled(true);
	this->setPosition(*this->initialPosition);
	this->action = WALK_LEFT;
	this->deadMillisecs = 0;
}


EnemyEntity::~EnemyEntity() {

}
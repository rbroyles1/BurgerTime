#include "EnemyEntity.h"
#include "BoxCollideComponent.h"
#include "EnemyRenderComponent.h"
#include "EnemyIngredientCollideComponent.h"
#include "WalkingRigidBodyComponent.h"
#include <cstdlib>

EnemyEntity::EnemyEntity(Engine* engine, Coordinate* position, EnemyType enemyType, PlayerEntity* player, std::vector<Entity*>* ingredients) : Entity(engine, position) {
	this->initialPosition = new Coordinate(position->getX(), position->getY());
	this->action = NO_ACTION;
	this->deadMillisecs = 0;
	this->hasMoved = false;
	this->canMove = true;

	std::vector<Entity*>* pepperVector = new std::vector<Entity*>();
	pepperVector->push_back(player->getPepper());
	
	this->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	this->addComponent(new EnemyRenderComponent(engine, this, enemyType));
	this->addComponent(new BoxCollideComponent(engine, this, ENEMY_PEPPERED, pepperVector));
	this->addComponent(new EnemyIngredientCollideComponent(engine, this, ingredients));
	this->addComponent(new WalkingRigidBodyComponent(this->engine, this, false));
}

void EnemyEntity::update(double dt) {
	Entity::update(dt);

	if (this->hasReceived(ENEMY_SQUASHED)) {
		this->action = DIE;
		this->canMove = false;
		this->engine->getMessageDispatcher()->send(ENEMY_SQUASHED);
	}
	if (this->hasReceived(ENEMY_PEPPERED) || this->action == STUNNED) {
		this->action = STUNNED;
		this->canMove = false;
	}
	if (this->hasReceived(ENEMY_UNPEPPERED)) {
		this->action = NO_ACTION;
		this->canMove = true;
		this->hasMoved = false;
	}
	if (this->hasReceived(ENEMY_ATTACK)) {
		this->action = NO_ACTION;
		this->canMove = false;
	}
	if (this->action == DIE) {
		this->deadMillisecs += dt * 1000;

		if (this->deadMillisecs >= 2000) {
			this->respawn();
		}
	}

	this->move();

	this->clearMessages();
}

void EnemyEntity::respawn() {
	this->setEnabled(true);
	this->setPosition(*this->initialPosition);
	this->action = NO_ACTION;
	this->deadMillisecs = 0;
	this->canMove = true;
	this->hasMoved = false;
}

CharacterAction EnemyEntity::getAction() {
	return this->action;
}

void EnemyEntity::move() {
	if (this->canMove) {
		std::vector<CharacterAction> possibleMoves = std::vector<CharacterAction>();

		if (this->isInIntersection() || !this->hasMoved) {
			if (!this->hasReceived(INTERSECT_LIMIT_LEFT)) {
				possibleMoves.push_back(WALK_LEFT);
			}
			if (!this->hasReceived(INTERSECT_LIMIT_RIGHT)) {
				possibleMoves.push_back(WALK_RIGHT);
			}

			if (this->hasReceived(INTERSECT_STAIRS)) {
				if (!this->hasReceived(INTERSECT_UP_STAIRS)) {
					possibleMoves.push_back(GO_UPSTAIRS);
				}
				if (!this->hasReceived(INTERSECT_DOWN_STAIRS)) {
					possibleMoves.push_back(GO_DOWNSTAIRS);
				}
			}

			this->action = possibleMoves.at(rand() % possibleMoves.size());
			this->hasMoved = this->action != NO_ACTION;
		}
	}
}

bool EnemyEntity::isInIntersection() {
	return this->hasReceived(ON_FLOOR) && 
		(this->hasReceived(INTERSECT_LIMIT_LEFT) || this->hasReceived(INTERSECT_LIMIT_RIGHT) || this->hasReceived(INTERSECT_STAIRS));
}

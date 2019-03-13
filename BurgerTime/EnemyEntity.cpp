#include "EnemyEntity.h"
#include "BoxCollideComponent.h"
#include "EnemyRenderComponent.h"
#include "EnemyIngredientCollideComponent.h"
#include "WalkingRigidBodyComponent.h"
#include <cstdlib>

EnemyEntity::EnemyEntity(Engine* engine, Coordinate* position, EnemyType enemyType, double idleTime, PlayerEntity* player, std::vector<Entity*>* ingredients) : Entity(engine, position) {
	this->initialPosition = new Coordinate(position->getX(), position->getY());
	this->action = NO_ACTION;
	this->deadTime = 0;
	this->idleTime = idleTime + INTRO_DURATION_MILLISECS / 1000.0;
	this->initialIdleTime = idleTime;
	this->hasMoved = false;
	this->canMove = true;
	this->player = player;

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
		this->engine->getMessageDispatcher()->send(ENEMY_ATTACK);
	}
	if (this->action == DIE) {
		this->deadTime += dt;

		if (this->deadTime >= 2) {
			this->respawn();
		}
	}

	if (this->idleTime > 0) {
		this->idleTime -= dt;
	}

	this->move();

	this->clearMessages();
}

void EnemyEntity::freeze() {
	this->action = NO_ACTION;
	this->canMove = false;
}

void EnemyEntity::respawn() {
	this->setEnabled(true);
	this->setPosition(*this->initialPosition);
	this->action = NO_ACTION;
	this->deadTime = 0;
	this->canMove = true;
	this->hasMoved = false;
	this->idleTime = this->initialIdleTime;
}

CharacterAction EnemyEntity::getAction() {
	return this->action;
}

void EnemyEntity::move() {
	if (this->canMove && this->idleTime <= 0) {
		std::vector<CharacterAction> possibleMoves = std::vector<CharacterAction>();
		std::vector<int> movesProbabilities = std::vector<int>();
		int currentProbability = 0;

		int diffX = (int)this->player->getPosition()->getX() - (int)this->position->getX();
		int diffY = (int)this->player->getPosition()->getY() - (int)this->position->getY();

		if (this->isInIntersection() || !this->hasMoved) {
			if (!this->hasReceived(INTERSECT_LIMIT_LEFT)) {
				currentProbability += diffX < 0 ? -diffX : 1;

				possibleMoves.push_back(WALK_LEFT);
				movesProbabilities.push_back(currentProbability);
			}
			if (!this->hasReceived(INTERSECT_LIMIT_RIGHT)) {
				currentProbability += diffX > 0 ? diffX : 1;

				possibleMoves.push_back(WALK_RIGHT);
				movesProbabilities.push_back(currentProbability);
			}

			if (this->hasReceived(INTERSECT_STAIRS)) {
				if (!this->hasReceived(INTERSECT_UP_STAIRS)) {
					currentProbability += diffY < 0 ? -diffY : 1;

					possibleMoves.push_back(GO_UPSTAIRS);
					movesProbabilities.push_back(currentProbability);
				}
				if (!this->hasReceived(INTERSECT_DOWN_STAIRS)) {
					currentProbability += diffY > 0 ? diffY : 1;
					possibleMoves.push_back(GO_DOWNSTAIRS);

					movesProbabilities.push_back(currentProbability);
				}
			}

			int random = rand() % currentProbability;
			int index = 0;

			for (index = 0; movesProbabilities.at(index) <= random; index++);

			this->action = possibleMoves.at(index);
			this->hasMoved = this->action != NO_ACTION;
		}
	}
}

bool EnemyEntity::isInIntersection() {
	return this->hasReceived(ON_FLOOR) && 
		(this->hasReceived(INTERSECT_LIMIT_LEFT) || this->hasReceived(INTERSECT_LIMIT_RIGHT) || this->hasReceived(INTERSECT_STAIRS));
}

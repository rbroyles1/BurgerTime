#pragma once
#include "Entity.h"
#include "PlayerEntity.h"

class PlayerEntity;
enum EnemyType { SAUSAGE, EGG, CUCUMBER };

class EnemyEntity : public Entity {
	Coordinate* initialPosition;
	CharacterAction action;
	PlayerEntity* player;

	double deadTime;
	double idleTime;
	double initialIdleTime;

	bool hasMoved;
	bool canMove;

public:
	EnemyEntity(Engine* engine, Coordinate* position, EnemyType enemyType, double idleTime, PlayerEntity* player, std::vector<Entity*>* ingredients);

	virtual void update(double dt);

	void onEnemyAttacked();
	void respawn();
	
	CharacterAction getAction();

private:
	void move();
	bool isInIntersection();
};


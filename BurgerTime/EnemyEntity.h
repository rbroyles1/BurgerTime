#pragma once
#include "Entity.h"
#include "PlayerEntity.h"

class PlayerEntity;
enum EnemyType { SAUSAGE };

class EnemyEntity : public Entity {
	Coordinate* initialPosition;

public:
	EnemyEntity(Engine* engine, Coordinate* position, EnemyType enemyType, PlayerEntity* player);

	void reset();

	~EnemyEntity();
};


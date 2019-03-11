#include "EnemyEntity.h"
#include "BoxCollideComponent.h"
#include "EnemyRenderComponent.h"

EnemyEntity::EnemyEntity(Engine* engine, Coordinate* position, EnemyType enemyType, PlayerEntity* player) : Entity(engine, position) {
	this->initialPosition = new Coordinate(position->getX(), position->getY());
	
	this->setBoundingBox(new BoundingBox(new Coordinate(2, 2)));
	this->addComponent(new EnemyRenderComponent(engine, this, enemyType));
}

void EnemyEntity::reset() {
	this->setPosition(*this->initialPosition);
}

EnemyEntity::~EnemyEntity() {

}

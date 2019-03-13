#include "EnemyPlayerCollideComponent.h"
#include "EnemyEntity.h"

EnemyPlayerCollideComponent::EnemyPlayerCollideComponent(Engine* engine, Entity* entity, std::vector<Entity*>* enemies) : Component(engine, entity) {
	this->enemies = enemies;
}

void EnemyPlayerCollideComponent::update(double dt) {
	for (Entity* collider: *this->enemies) {
		if (this->entity != collider) {
			EnemyEntity* enemy = (EnemyEntity*)collider;

			BoundingBox* thisBox = this->entity->getBoundingBox();
			BoundingBox* otherBox = new BoundingBox(new Coordinate(2,2));

			if (thisBox->isIntersecting(this->entity->getPosition(), enemy->getPosition(), otherBox)) {
				if (enemy->getAction() != DIE && enemy->getAction() != STUNNED) {
					this->entity->receive(ENEMY_ATTACK);
					enemy->receive(ENEMY_ATTACK);
				}
			}

			delete otherBox;
		}
	}
}
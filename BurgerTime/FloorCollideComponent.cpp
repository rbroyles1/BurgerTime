#include "FloorCollideComponent.h"

FloorCollideComponent::FloorCollideComponent(Engine * engine, Entity * entity, std::vector<Entity*>* floors) : Component(engine, entity) {
	this->floors = floors;
}

void FloorCollideComponent::update(double dt) {
	for (Entity* floor : *this->floors) {
		BoundingBox* entityBox = this->entity->getBoundingBox();
		BoundingBox* floorBox = floor->getBoundingBox();
		double heightDiff = floor->getPosition()->getY() - this->entity->getPosition()->getY();

		bool onFloor = entityBox->isIntersecting(this->entity->getPosition(), floor->getPosition(), floorBox)
			&& heightDiff > 6.5 && heightDiff < 9.5;

		if (onFloor) {
			this->entity->receive(ON_FLOOR);
		}
	}
}

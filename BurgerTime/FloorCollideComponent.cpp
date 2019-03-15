#include "FloorCollideComponent.h"

FloorCollideComponent::FloorCollideComponent(Engine * engine, Entity * entity, Message message, std::vector<Entity*>* floors, bool isPlayer, Entity * additionalEntity) : Component(engine, entity) {
	this->message = message;
	this->floors = floors;
	this->additionalEntity = additionalEntity;
	this->isPlayer = isPlayer;
}

FloorCollideComponent::FloorCollideComponent(Engine * engine, Entity * entity, Message message,std::vector<Entity*>* floors, bool isPlayer)
	: FloorCollideComponent(engine, entity, message, floors, isPlayer, nullptr) { }


void FloorCollideComponent::update(double dt) {
	for (Entity* floor : *this->floors) {
		BoundingBox* entityBox = this->entity->getBoundingBox();
		BoundingBox* floorBox = floor->getBoundingBox();
		BoundingBox nearFloorBox = BoundingBox(new Coordinate(16, 8));

		double heightDiff = floor->getPosition()->getY() - this->entity->getPosition()->getY();

		bool nearFloor = nearFloorBox.isIntersecting(floor->getPosition(), this->entity->getPosition(), entityBox)
			&& heightDiff > 3 && heightDiff < 13;
		bool onFloor = entityBox->isIntersecting(this->entity->getPosition(), floor->getPosition(), floorBox)
			&& heightDiff > 6.5 && heightDiff < 9.5;

		if (this->isPlayer && nearFloor && !onFloor) {
			((PlayerEntity*)this->entity)->notifyNearFloor(floor);
		}

		if (onFloor) {
			this->entity->receive(this->message);

			if (this->additionalEntity != nullptr) {
				this->additionalEntity->receive(this->message);
			}
		}
	}
}

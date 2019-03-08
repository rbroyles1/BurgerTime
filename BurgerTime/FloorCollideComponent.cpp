#include "FloorCollideComponent.h"

FloorCollideComponent::FloorCollideComponent(Engine * engine, Entity * entity, Message message, std::vector<Entity*>* floors, Entity * additionalEntity) : Component(engine, entity) {
	this->message = message;
	this->floors = floors;
	this->additionalEntity = additionalEntity;
}

FloorCollideComponent::FloorCollideComponent(Engine * engine, Entity * entity, Message message, std::vector<Entity*>* floors) 
	: FloorCollideComponent(engine, entity, message, floors, nullptr) { }


void FloorCollideComponent::update(double dt) {
	for (Entity* floor : *this->floors) {
		BoundingBox* entityBox = this->entity->getBoundingBox();
		BoundingBox* floorBox = floor->getBoundingBox();
		double heightDiff = floor->getPosition()->getY() - this->entity->getPosition()->getY();

		bool onFloor = entityBox->isIntersecting(this->entity->getPosition(), floor->getPosition(), floorBox)
			&& heightDiff > 6.5 && heightDiff < 9.5;

		if (onFloor) {
			this->entity->receive(this->message);

			if (this->additionalEntity != nullptr) {
				this->additionalEntity->receive(this->message);
			}
		}
	}
}

#include "BoxCollideComponent.h"
#include <cmath>

BoxCollideComponent::BoxCollideComponent(Engine * engine, Entity * entity, Coordinate* boxSize, Message message, std::vector<BoxCollideComponent*>* colliders) : Component(engine, entity) {
	this->boxSize = boxSize;
	this->colliders = colliders;
	this->message = message;
}

void BoxCollideComponent::update(double dt) {
	for (BoxCollideComponent* collider : *this->colliders) {
		if (this != collider) {
			Coordinate* thisCenter = this->entity->getPosition();
			Coordinate* otherCenter = collider->entity->getPosition();
			Coordinate* thisBox = this->boxSize;
			Coordinate* otherBox = collider->boxSize;

			bool intersection = abs(thisCenter->getX() - otherCenter->getX()) * 2 < thisBox->getX() + thisBox->getX()
				&& abs(thisCenter->getY() - otherCenter->getY()) * 2 < thisBox->getY() + thisBox->getY();

			if (intersection) {
				this->entity->receive(this->message);
				collider->entity->receive(this->message);
			}
		}
	}
}
#include "BoxCollideComponent.h"
#include "BoundingBox.h"
#include <cmath>

BoxCollideComponent::BoxCollideComponent(Engine* engine, Entity* entity, Message message, std::vector<Entity*>* potentialColliders) : Component(engine, entity) {
	this->colliders = potentialColliders;
	this->message = message;
}

void BoxCollideComponent::update(double dt) {
	for (Entity* collider : *this->colliders) {
		if (this->entity != collider) {
			BoundingBox* thisBox = this->entity->getBoundingBox();
			BoundingBox* otherBox = collider->getBoundingBox();

			if (thisBox->isIntersecting(this->entity->getPosition(), collider->getPosition(), otherBox)) {
				this->entity->receive(this->message);
			}
		}
	}
}
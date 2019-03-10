#include "FloorIngredientCollideComponent.h"

FloorIngredientCollideComponent::FloorIngredientCollideComponent(Engine* engine, Entity* ingredient, std::vector<Entity*>* floors) : Component(engine, ingredient) {
	this->floors = floors;
}

void FloorIngredientCollideComponent::update(double dt) {
	for (Entity* floor : *this->floors) {
		BoundingBox* ingredientBox = this->entity->getBoundingBox();
		BoundingBox* floorBox = floor->getBoundingBox();
		double heightDiff = floor->getPosition()->getY() - this->entity->getPosition()->getY();

		bool onFloor = ingredientBox->isIntersecting(this->entity->getPosition(), floor->getPosition(), floorBox)
			&& heightDiff > 0 && heightDiff < 2;

		if (onFloor) {
			this->entity->receive(INGREDIENT_ON_FLOOR);
			this->entity->setPosition(*floor->getPosition());

			ingredientBox->isIntersecting(this->entity->getPosition(), floor->getPosition(), floorBox);

			floor->receive(INGREDIENT_ON_FLOOR);
		}
	}
}

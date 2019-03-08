#include "IngredientRigidBodyComponent.h"
#include "IngredientEntity.h"
#include "Constants.h"

IngredientRigidBodyComponent::IngredientRigidBodyComponent(Engine* engine, Entity* entity) : RigidBodyComponent(engine, entity) { }

void IngredientRigidBodyComponent::update(double dt) {
	if (((IngredientEntity*)this->entity)->isFalling()) {
		this->velocity->setY(INGREDIENT_FALL_VELOCITY);
	}
	else {
		this->velocity->setY(0);
	}

	RigidBodyComponent::update(dt);
}
#include "EnemyIngredientCollideComponent.h"
#include "IngredientEntity.h"

EnemyIngredientCollideComponent::EnemyIngredientCollideComponent(Engine* engine, Entity* enemy, std::vector<Entity*>* ingredients) : Component(engine, enemy) {
	this->ingredients = ingredients;
}

void EnemyIngredientCollideComponent::update(double dt) {
	for (Entity* ingredient : *this->ingredients) {
		BoundingBox* enemyBox = this->entity->getBoundingBox();
		BoundingBox* ingredientBox = ingredient->getBoundingBox();

		bool intersect = enemyBox->isIntersecting(this->entity->getPosition(), ingredient->getPosition(), ingredientBox);

		if (intersect && ((IngredientEntity*) ingredient)->isFalling()) {
			this->entity->receive(ENEMY_SQUASHED);
		}
	}
}
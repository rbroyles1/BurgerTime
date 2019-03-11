#pragma once
#include "Component.h"
class EnemyIngredientCollideComponent : public Component {
	std::vector<Entity*>* ingredients;

public:
	EnemyIngredientCollideComponent(Engine* engine, Entity* enemy, std::vector<Entity*>* ingredients);

	virtual void update(double dt);
};


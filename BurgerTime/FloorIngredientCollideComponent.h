#pragma once
#include "Component.h"

class FloorIngredientCollideComponent : public Component {
	std::vector<Entity*>* floors;

public:
	FloorIngredientCollideComponent(Engine* engine, Entity* ingredient, std::vector<Entity*>* floors);
	
	virtual void update(double dt);
};


#pragma once
#include "PlayerEntity.h"

enum Ingredient {BREAD_BOTTOM, BREAD_TOP, CHEESE, LETTUCE, MEAT, TOMATO};

class IngredientEntity : public Entity {
	PlayerEntity* player;

	std::vector<Entity*>* ingredientEntities;
	bool* pushedDown;

public:
	IngredientEntity(Engine* engine, Coordinate* position, PlayerEntity* player, Ingredient ingredient);

	virtual void update(double dt);
	virtual void receive(Message message);

	~IngredientEntity();

private:
	void getSpritePattern(char* destinationBuffer, Ingredient ingredient);
};


#pragma once
#include "PlayerEntity.h"

enum Ingredient {BREAD_BOTTOM, BREAD_TOP, CHEESE, LETTUCE, MEAT, TOMATO};

class IngredientEntity : public Entity {
	PlayerEntity* player;

	std::vector<Entity*>* ingredientEntities;
	bool* pushedDown;
	bool falling;

public:
	IngredientEntity(Engine* engine, Coordinate* position, PlayerEntity* player, Ingredient ingredient, std::vector<Entity*>* floors);

	virtual void update(double dt);
	virtual void receive(Message message);
	virtual void setPosition(Coordinate& position);

	bool isFalling();

	~IngredientEntity();

private:
	void getSpritePattern(char* destinationBuffer, Ingredient ingredient);
	void onPlayerStep(int i);
	void onFloorHit();
};


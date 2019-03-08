#define _CRT_SECURE_NO_WARNINGS

#include "IngredientEntity.h"
#include "Sprite.h"
#include "Engine.h"
#include "RenderComponent.h"
#include "FloorCollideComponent.h"
#include <string>

IngredientEntity::IngredientEntity(Engine* engine, Coordinate* position, PlayerEntity* player, Ingredient ingredient) : Entity(engine, position) {
	char spritePattern[1000];

	this->player = player;
	this->ingredientEntities = new std::vector<Entity*>();
	this->pushedDown = new bool[4]();

	this->getSpritePattern(spritePattern, ingredient);

	for (int i = 0; i < 4; i++) {
		Coordinate* partPosition = new Coordinate(position->getX() - 12 + i * 8, position->getY());
		Entity* ingredientPart = new Entity(engine, partPosition);
		char spritePath[1000];

		snprintf(spritePath, 1000, spritePattern, i + 1);
		Sprite* partSprite = new Sprite(engine->getRenderer(), spritePath);
		ingredientPart->addComponent(new RenderComponent(engine, ingredientPart, partSprite, new Coordinate(0, 2)));

		std::vector<Entity*>* wrappedPart = new std::vector<Entity*>();
		wrappedPart->push_back(ingredientPart);
		player->addComponent(new FloorCollideComponent(engine, player, (Message) (ON_INGREDIENT_1 + i), wrappedPart, this));

		ingredientPart->setBoundingBox(new BoundingBox(new Coordinate(1, 2)));

		this->ingredientEntities->push_back(ingredientPart);
	}
}

void IngredientEntity::update(double dt) {
	Entity::update(dt);

	for (Entity* ingredientPart : *this->ingredientEntities) {
		ingredientPart->update(dt);
	}
}

void IngredientEntity::receive(Message message) {
	int i = message - ON_INGREDIENT_1;

	if (i >= 0 && i < 4 && !this->pushedDown[i]) {
		Coordinate* position = this->ingredientEntities->at(i)->getPosition();

		this->pushedDown[i] = true;
		position->setY(position->getY() + 1);
	}
}

void IngredientEntity::getSpritePattern(char * destinationBuffer, Ingredient ingredient) {
	switch (ingredient) {
		case BREAD_BOTTOM:
			strcpy(destinationBuffer, "resources/sprites/bottom (%d).bmp");
			break;
		case BREAD_TOP:
			strcpy(destinationBuffer, "resources/sprites/top (%d).bmp");
			break;
		case CHEESE:
			strcpy(destinationBuffer, "resources/sprites/cheese (%d).bmp");
			break;
		case LETTUCE:
			strcpy(destinationBuffer, "resources/sprites/lettuce (%d).bmp");
			break;
		case MEAT:
			strcpy(destinationBuffer, "resources/sprites/meat (%d).bmp");
			break;
		case TOMATO:
			strcpy(destinationBuffer, "resources/sprites/tomato (%d).bmp");
			break;
		}
}

IngredientEntity::~IngredientEntity() {
	for (auto it = this->ingredientEntities->begin(); it != this->ingredientEntities->end(); it++) {
		delete *it;
	}

	delete this->ingredientEntities;
	delete[] this->pushedDown;
}

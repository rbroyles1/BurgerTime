#define _CRT_SECURE_NO_WARNINGS

#include "IngredientEntity.h"
#include "Sprite.h"
#include "RenderComponent.h"
#include "FloorCollideComponent.h"
#include "IngredientRigidBodyComponent.h"
#include "FloorIngredientCollideComponent.h"
#include <string>

IngredientEntity::IngredientEntity(Engine* engine, Coordinate* position, PlayerEntity* player, Ingredient ingredient, std::vector<Entity*>* ingredients, std::vector<Entity*>* floors) : Entity(engine, position) {
	char spritePattern[1000];

	this->player = player;
	this->ingredientEntities = new std::vector<Entity*>();
	this->pushedDown = new bool[4]();
	this->falling = false;

	this->getSpritePattern(spritePattern, ingredient);

	for (int i = 0; i < 4; i++) {
		Coordinate* partPosition = new Coordinate(position->getX() - 12 + i * 8, position->getY());
		Entity* ingredientPart = new Entity(engine, partPosition);
		char spritePath[1000];

		snprintf(spritePath, 1000, spritePattern, i + 1);
		Sprite* partSprite = new Sprite(engine->getRenderer(), spritePath);
		ingredientPart->addComponent(new RenderComponent(engine, ingredientPart, partSprite, new Coordinate(0, -2)));

		std::vector<Entity*>* wrappedPart = new std::vector<Entity*>();
		wrappedPart->push_back(ingredientPart);
		player->addComponent(new FloorCollideComponent(engine, player, (Message) (ON_INGREDIENT_1 + i), wrappedPart, false, this));

		ingredientPart->setBoundingBox(new BoundingBox(new Coordinate(1, 2)));

		this->ingredientEntities->push_back(ingredientPart);
	}

	this->setBoundingBox(new BoundingBox(new Coordinate(32, 2)));

	this->addComponent(new IngredientRigidBodyComponent(engine, this));
	this->addComponent(new BoxCollideComponent(engine, this, INGREDIENT_INGREDIENT_HIT, ingredients));
	this->addComponent(new FloorIngredientCollideComponent(engine, this, floors));
}

void IngredientEntity::update(double dt) {
	Entity::update(dt);

	for (Entity* ingredientPart : *this->ingredientEntities) {
		ingredientPart->update(dt);
	}
}

void IngredientEntity::receive(Message message) {
	int i = message - ON_INGREDIENT_1;

	if (message >= ON_INGREDIENT_1 && message <= ON_INGREDIENT_4) {
		this->onPlayerStep(message - ON_INGREDIENT_1);
	}
	else if (message == INGREDIENT_ON_FLOOR) {
		this->onFloorHit();
	}
	else if (message == INGREDIENT_INGREDIENT_HIT) {
		this->onIngredientHit();
	}
}

void IngredientEntity::setPosition(Coordinate& position) {
	this->position->setY(position.getY());

	for (int i = 0; i < 4; i++) {
		this->ingredientEntities->at(i)->getPosition()->setY(position.getY() + (this->pushedDown[i]? 1 : 0));
	}
}

bool IngredientEntity::isFalling() {
	return this->falling;
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

void IngredientEntity::onPlayerStep(int i) {
	if (i >= 0 && i < 4 && !this->pushedDown[i]) {
		this->pushedDown[i] = true;
		this->engine->getMessageDispatcher()->send(ON_INGREDIENT_1);
	}

	bool allPushedDown = true;

	for (int i = 0; i < 4; i++) {
		allPushedDown = allPushedDown && this->pushedDown[i];
	}

	this->falling = allPushedDown;
}

void IngredientEntity::onFloorHit() {
	this->falling = false;
	
	for (int i = 0; i < 4; i++) {
		this->pushedDown[i] = false;
	}

	this->engine->getMessageDispatcher()->send(INGREDIENT_FLOOR_HIT);
}

void IngredientEntity::onIngredientHit() {
	if (this->falling) {
		Coordinate* position = this->getPosition();
		position->setY(position->getY() - 4);

		this->setPosition(*position);
		this->engine->getMessageDispatcher()->send(INGREDIENT_INGREDIENT_HIT);
	}

	this->falling = true;
}

IngredientEntity::~IngredientEntity() {
	for (auto it = this->ingredientEntities->begin(); it != this->ingredientEntities->end(); it++) {
		delete *it;
	}

	delete this->ingredientEntities;
	delete[] this->pushedDown;
}

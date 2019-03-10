#pragma once
#include <vector>
#include "BoxCollideComponent.h"
#include "PlayerEntity.h"
#include "IngredientEntity.h"
#include "InputComponent.h"

class Engine;
class Entity;
class BoxCollideComponent;

enum Field {FLOOR, STAIR, NO_FIELD};
enum Ingredient;

class Game : public Entity {
	std::vector<Entity*>* entities;
	std::vector<Entity*>* floors;
	std::vector<Entity*>* leftFloorsLimits;
	std::vector<Entity*>* rightFloorsLimits;
	std::vector<Entity*>* stairs;
	std::vector<Entity*>* upStairsLimits;
	std::vector<Entity*>* downStairsLimits;
	std::vector<Entity*>* ingredients;

	PlayerEntity* player;
	InputComponent* input;
	Field previousField;
	Coordinate* previousFieldPosition;

	int score;
	int lives;
	int totalIngredients;
	int currentFinishedIngredients;

public:
	Game(Engine* engine);

	virtual void init();
	virtual void update(double dt);
	virtual void receive(Message message);
	void addEntity(Entity* entity);

	void addFloor(Coordinate* position, int type);
	void addStair(Coordinate* position);
	void addIngredient(Coordinate* position, Ingredient ingredient);
	void addDish(Coordinate* position);
	void addPlayer(Coordinate* position);

	void ingredientFinished();
	void increaseScore(int increase);
	int getScore();
	void increaseLives();
	int getLives();
	
	virtual ~Game();

private:
	void createPlayer();
	void createGameComponents();
	void createFpsCounter();
	void createHUD();
	void createLevel();

	void updateLimits(Field newField, Coordinate* position);
	void addStartingLimit(Field newField, Coordinate* position);
	void addEndingLimit();

	void createFloorLimit(Coordinate* position, int type);
	void createStairLimit(Coordinate* position, int type);

	void victory();
};
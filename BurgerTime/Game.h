#pragma once
#include <vector>
#include "BoxCollideComponent.h"
#include "PlayerEntity.h"
#include "IngredientEntity.h"
#include "InputComponent.h"
#include "SDL_mixer.h"

class Engine;
class Entity;
class BoxCollideComponent;

enum Field {FLOOR, STAIR, NO_FIELD};
enum Ingredient;

class Game : public Entity {
	std::string* chosenLevel;

	std::vector<Entity*>* entities;
	std::vector<Entity*>* floors;
	std::vector<Entity*>* leftFloorsLimits;
	std::vector<Entity*>* rightFloorsLimits;
	std::vector<Entity*>* stairs;
	std::vector<Entity*>* upStairsLimits;
	std::vector<Entity*>* downStairsLimits;
	std::vector<Entity*>* ingredients;
	std::vector<Entity*>* enemies;

	PlayerEntity* player;
	Entity* lantern;
	Entity* gameOverText;
	InputComponent* input;
	Field previousField;
	Coordinate* previousFieldPosition;

	int score;
	int lives;
	int pepper;
	int totalIngredients;
	int currentFinishedIngredients;

	double introTime;

	bool reset;

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
	void addEnemy(Coordinate* position, EnemyType enemyType, double idleTime);
	void addPlayer(Coordinate* position);

	void notifyKeyDown(SDL_Keycode key);
	void notifyKeyUp(SDL_Keycode key);

	int getScore();
	int getLives();
	int getPepper();
	
	virtual ~Game();

private:
	void createPlayer();
	void createGameComponents();
	void createFpsCounter();
	void createHUD();
	void createLevel();

	void setWalkingEntityColliders(Entity* entity);

	void updateLimits(Field newField, Coordinate* position);
	void addStartingLimit(Field newField, Coordinate* position);
	void addEndingLimit();

	void createFloorLimit(Coordinate* position, int type);
	void createStairLimit(Coordinate* position, int type);

	void increaseScore(int increase);
	void increaseLives();
	void ingredientFinished();
	void pepperThrown();
	void enemyAttacked();
	void playerDied();
	void victory();

	void initFields();
	void performSubscriptions();
	void waitForIntro(double dt);
	void loadNewLevel();
	void freeResources(bool freeComponents);
};
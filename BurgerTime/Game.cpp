#include "Game.h"
#include "Engine.h"
#include "Entity.h"
#include "Text.h"
#include "FpsCounterComponent.h"
#include "InputComponent.h"
#include "BoxCollideComponent.h"
#include "PlayerEntity.h"
#include "PlayerRigidBodyComponent.h"
#include "RenderComponent.h"
#include "PlayerRenderComponent.h"
#include "LevelManager.h"
#include "DishFakeFloorEntity.h"
#include "ScoreCounterComponent.h"
#include "LivesTrackerEntity.h"

// TODO reconsider if Receiver.h is really necessary
Game::Game(Engine* engine) : Entity(engine) {
	this->entities = new std::vector<Entity*>();
	this->floors = new std::vector<Entity*>();
	this->leftFloorsLimits = new std::vector<Entity*>();
	this->rightFloorsLimits = new std::vector<Entity*>();
	this->stairs = new std::vector<Entity*>();
	this->upStairsLimits = new std::vector<Entity*>();
	this->downStairsLimits = new std::vector<Entity*>();
	this->ingredients = new std::vector<Entity*>();

	this->input = new InputComponent(this->engine, this);
	this->player = nullptr;
	this->previousField = NO_FIELD;
	this->previousFieldPosition = new Coordinate();

	this->score = 0;
	this->totalIngredients = 0;
	this->currentFinishedIngredients = 0;
	this->lives = INITIAL_LIVES;
}

void Game::init() {
	this->createHUD();
	//this->createFpsCounter();
	this->createGameComponents();
	this->createPlayer();
	this->createLevel();

	this->engine->getMessageDispatcher()->subscribe(EXIT, this);
	this->addEntity(this->player);

	Entity::init();
}

void Game::update(double dt) {
	Entity::update(dt);

	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		(*it)->update(dt);
	}
}

void Game::receive(Message message) {
	if (message == EXIT) {
		this->engine->stop();
	}
}

void Game::addEntity(Entity* entity) {
	this->entities->push_back(entity);
}

void Game::createPlayer() {
	this->player = new PlayerEntity(this->engine, position);
	this->player->setPlayerColliders(this->floors, this->leftFloorsLimits, this->rightFloorsLimits, this->stairs, this->upStairsLimits, this->downStairsLimits);
}

void Game::createGameComponents() {
	this->addComponent(this->input);
}

void Game::createFpsCounter() {
	Entity* fpsCounter = new Entity(this->engine, new Coordinate(10, 10));
	Text* text = new Text(this->engine->getRenderer(), "space_invaders.ttf", 8);

	fpsCounter->addComponent(new FpsCounterComponent(this->engine, fpsCounter, text));
	this->addEntity(fpsCounter);
}

void Game::createHUD() {
	Entity* scoreText = new Entity(this->engine, new Coordinate(24, 0));
	LivesTrackerEntity* livesTracker = new LivesTrackerEntity(this->engine, new Coordinate(8, 232), this);
	
	scoreText->addComponent(new ScoreCounterComponent(this->engine, scoreText, this));

	this->addEntity(scoreText);
	this->addEntity(livesTracker);
}

void Game::createLevel() {
	LevelManager manager(this);

	manager.loadLevel("resources/levels/default.bgtm");
	this->addEndingLimit();
}

void Game::addFloor(Coordinate* position, int type) {
	Entity* floor = new Entity(this->engine, position);
	Sprite* floorSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/floor.bmp");

	floor->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));
	floor->addComponent(new RenderComponent(this->engine, floor, floorSprite));

	this->floors->push_back(floor);
	this->addEntity(floor);

	this->updateLimits(FLOOR, position);
}

void Game::addStair(Coordinate* position) {
	Entity* stair = new Entity(this->engine, position);
	Sprite* stairSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/stairs.bmp");

	stair->setBoundingBox(new BoundingBox(new Coordinate(1, 16)));
	stair->addComponent(new RenderComponent(this->engine, stair, stairSprite));

	this->stairs->push_back(stair);
	this->addEntity(stair);

	this->updateLimits(STAIR, position);
}

void Game::addIngredient(Coordinate* position, Ingredient ingredient) {
	IngredientEntity* ingredient1 = new IngredientEntity(this->engine, position, this->player, ingredient, this, this->ingredients, this->floors);

	this->totalIngredients++;
	this->ingredients->push_back(ingredient1);
	this->addEntity(ingredient1);
}

void Game::addDish(Coordinate* position) {
	Entity* dish = new Entity(this->engine, position);
	Sprite* sprite = new Sprite(engine->getRenderer(), "resources/sprites/dish.bmp");

	Coordinate* fakeFloorPosition = new Coordinate(position->getX(), position->getY());
	DishFakeFloorEntity* fakeFloor = new DishFakeFloorEntity(this->engine, fakeFloorPosition, this);

	dish->addComponent(new RenderComponent(engine, dish, sprite));

	this->floors->push_back(fakeFloor);
	this->addEntity(dish);
}

void Game::addPlayer(Coordinate* position) {
	this->player->setPosition(*position);
}

void Game::ingredientFinished() {
	this->currentFinishedIngredients++;

	if (this->currentFinishedIngredients >= this->totalIngredients) {
		this->victory();
	}
}

void Game::increaseScore(int increase) {
	this->score += increase;
}

int Game::getScore() {
	return this->score;
}

void Game::increaseLives() {
	if (this->lives < MAX_LIVES) {
		this->lives++;
	}
}

int Game::getLives() {
	return this->lives;
}

void Game::updateLimits(Field newField, Coordinate* position) {
	bool isNewUnit = (newField != this->previousField)
		|| (newField == FLOOR && (position->getY() != this->previousFieldPosition->getY() 
			|| abs(position->getX() - this->previousFieldPosition->getX()) > 16))
		|| (newField == STAIR && (position->getX() != this->previousFieldPosition->getX()
			|| abs(position->getY() - this->previousFieldPosition->getY()) > 16));

	if (isNewUnit) {
		this->addStartingLimit(newField, position);
		this->addEndingLimit();
	}

	this->previousField = newField;

	this->previousFieldPosition->setX(position->getX());
	this->previousFieldPosition->setY(position->getY());
}

void Game::addStartingLimit(Field newField, Coordinate * position) {
	if (newField == FLOOR) {
		Coordinate* limitPosition = new Coordinate(position->getX() - 16, position->getY());
		this->createFloorLimit(limitPosition, 0);
	}
	else if (newField == STAIR) {
		Coordinate* limitPosition = new Coordinate(position->getX(), position->getY() - 24);
		this->createStairLimit(limitPosition, 0);
	}
}

void Game::addEndingLimit() {
	if (this->previousField == FLOOR) {
		Coordinate* limitPosition = new Coordinate(this->previousFieldPosition->getX() + 16, this->previousFieldPosition->getY());
		this->createFloorLimit(limitPosition, 1);
	}
	else if (this->previousField == STAIR) {
		Coordinate* limitPosition = new Coordinate(this->previousFieldPosition->getX(), this->previousFieldPosition->getY() + 9);
		this->createStairLimit(limitPosition, 1);
	}
}

void Game::createFloorLimit(Coordinate* position, int type) {
	Entity* limit = new Entity(this->engine, position);
	limit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));
	position->setY(position->getY() - 5);

	if (type == 0) {
		//limit->addComponent(new RenderComponent(this->engine, limit, new Sprite(this->engine->getRenderer(), "resources/sprites/cheese (1).bmp")));
		this->leftFloorsLimits->push_back(limit);
	}
	else {
		//limit->addComponent(new RenderComponent(this->engine, limit, new Sprite(this->engine->getRenderer(), "resources/sprites/meat (1).bmp")));
		this->rightFloorsLimits->push_back(limit);
	}

	//this->addEntity(limit);
}

void Game::createStairLimit(Coordinate* position, int type) {
	Entity* stairLimit = new Entity(this->engine, position);
	stairLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));

	if (type == 0) {
		//stairLimit->addComponent(new RenderComponent(this->engine, stairLimit, new Sprite(this->engine->getRenderer(), "resources/sprites/top (1).bmp")));
		this->upStairsLimits->push_back(stairLimit);
	}
	else {
		//stairLimit->addComponent(new RenderComponent(this->engine, stairLimit, new Sprite(this->engine->getRenderer(), "resources/sprites/bottom (1).bmp")));
		this->downStairsLimits->push_back(stairLimit);
	}

	//this->addEntity(stairLimit);
}

void Game::victory() {
	this->input->setEnabled(false);
	this->engine->getMessageDispatcher()->send(GAME_VICTORY);
}

Game::~Game() {
	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		delete *it;
	}

	delete this->entities;
	delete this->floors;
	delete this->leftFloorsLimits;
	delete this->rightFloorsLimits;
	delete this->stairs;
	delete this->upStairsLimits;
	delete this->downStairsLimits;

	delete this->previousFieldPosition;
}
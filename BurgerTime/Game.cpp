#include "Game.h"
#include "Engine.h"
#include "Entity.h"
#include "Text.h"
#include "FpsCounterComponent.h"
#include "InputComponent.h"
#include "BoxCollideComponent.h"
#include "PlayerEntity.h"
#include "RenderComponent.h"
#include "PlayerRenderComponent.h"
#include "LevelManager.h"
#include "DishFakeFloorEntity.h"
#include "ScoreCounterComponent.h"
#include "LivesTrackerEntity.h"
#include "FloorCollideComponent.h"
#include "TextRenderComponent.h"
#include "PepperCounterComponent.h"

// TODO change floor color
// TODO maybe allow the player to control one enemy
// TODO reconsider if Receiver.h is really necessary
// TODO change all int millisecs to double secs
// TODO reduce enemies bounding box
// TODO fix enemies are able to kill you when they are stunned
Game::Game(Engine* engine) : Entity(engine) {
	this->entities = new std::vector<Entity*>();
	this->floors = new std::vector<Entity*>();
	this->leftFloorsLimits = new std::vector<Entity*>();
	this->rightFloorsLimits = new std::vector<Entity*>();
	this->stairs = new std::vector<Entity*>();
	this->upStairsLimits = new std::vector<Entity*>();
	this->downStairsLimits = new std::vector<Entity*>();
	this->ingredients = new std::vector<Entity*>();
	this->enemies = new std::vector<Entity*>();

	this->input = new InputComponent(this->engine, this);
	this->player = nullptr;
	
	this->clear();
}

void Game::init() {
	//this->createFpsCounter();
	this->createGameComponents();
	this->createPlayer();
	this->createLevel();
	this->createHUD();

	this->addEntity(this->player);
	this->addEntity(this->player->getPepper());

	this->engine->getMessageDispatcher()->subscribe(EXIT, this);
	this->engine->getMessageDispatcher()->subscribe(INGREDIENT_FLOOR_HIT, this);
	this->engine->getMessageDispatcher()->subscribe(INGREDIENT_FINISHED, this);
	this->engine->getMessageDispatcher()->subscribe(PEPPER_THROWN, this);
	this->engine->getMessageDispatcher()->subscribe(PLAYER_DIED, this);
	this->engine->getMessageDispatcher()->subscribe(ENEMY_SQUASHED, this);

	Entity::init();
}

void Game::update(double dt) {
	Entity::update(dt);

	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		(*it)->update(dt);
	}
}

void Game::receive(Message message) {
	switch (message) {
		case EXIT:
			this->engine->stop();
			break;
		case INGREDIENT_FLOOR_HIT:
			this->increaseScore(50);
			break;
		case INGREDIENT_FINISHED:
			this->ingredientFinished();
			break;
		case PEPPER_THROWN:
			this->pepperThrown();
			break;
		case ENEMY_SQUASHED:
			this->increaseScore(100);
			break;
		case PLAYER_DIED:
			this->playerDied();
			break;
	}
}

void Game::addEntity(Entity* entity) {
	this->entities->push_back(entity);
}

void Game::clear() {
	this->entities->clear();
	this->floors->clear();
	this->leftFloorsLimits->clear();
	this->rightFloorsLimits->clear();
	this->stairs->clear();
	this->upStairsLimits->clear();
	this->downStairsLimits->clear();
	this->ingredients->clear();
	this->enemies->clear();

	this->previousField = NO_FIELD;
	this->previousFieldPosition = new Coordinate();

	this->score = 0;
	this->totalIngredients = 0;
	this->currentFinishedIngredients = 0;
	this->lives = INITIAL_LIVES;
	this->pepper = INITIAL_PEPPER;
}

void Game::createPlayer() {
	this->player = new PlayerEntity(this->engine, new Coordinate(), this->enemies, this);
	this->setWalkingEntityColliders(this->player);
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
	scoreText->addComponent(new ScoreCounterComponent(this->engine, scoreText, this));
	this->addEntity(scoreText);

	LivesTrackerEntity* livesTracker = new LivesTrackerEntity(this->engine, new Coordinate(8, 232), this);
	this->addEntity(livesTracker);

	Entity* pepperText = new Entity(this->engine, new Coordinate(200, 0));
	pepperText->addComponent(new PepperCounterComponent(this->engine, pepperText, this));
	this->addEntity(pepperText);

	this->gameOverText = new Entity(this->engine, new Coordinate(70, 120));
	this->gameOverText->addComponent(new TextRenderComponent(this->engine, this->gameOverText, new std::string("GAME OVER"),
		new Text(this->engine->getRenderer(), "space_invaders.ttf", 16)));
	this->gameOverText->setEnabled(false);

	this->addEntity(this->gameOverText);
}

void Game::createLevel() {
	LevelManager manager(this);

	manager.loadLevel("resources/levels/default.bgtm");
	this->addEndingLimit();
}

void Game::setWalkingEntityColliders(Entity* entity) {
	FloorCollideComponent* floorBox = new FloorCollideComponent(this->engine, entity, ON_FLOOR, floors);
	BoxCollideComponent* leftBox = new BoxCollideComponent(this->engine, entity, INTERSECT_LIMIT_LEFT, leftFloorsLimits);
	BoxCollideComponent* rightBox = new BoxCollideComponent(this->engine, entity, INTERSECT_LIMIT_RIGHT, rightFloorsLimits);
	BoxCollideComponent* stairsBox = new BoxCollideComponent(this->engine, entity, INTERSECT_STAIRS, stairs);
	BoxCollideComponent* upStairsBox = new BoxCollideComponent(this->engine, entity, INTERSECT_UP_STAIRS, upStairsLimits);
	BoxCollideComponent* downStairsBox = new BoxCollideComponent(this->engine, entity, INTERSECT_DOWN_STAIRS, downStairsLimits);

	entity->addComponent(floorBox);
	entity->addComponent(leftBox);
	entity->addComponent(rightBox);
	entity->addComponent(stairsBox);
	entity->addComponent(upStairsBox);
	entity->addComponent(downStairsBox);
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
	IngredientEntity* ingredient1 = new IngredientEntity(this->engine, position, this->player, ingredient, this->ingredients, this->floors);

	this->totalIngredients++;
	this->ingredients->push_back(ingredient1);
	this->addEntity(ingredient1);
}

void Game::addDish(Coordinate* position) {
	Entity* dish = new Entity(this->engine, position);
	Sprite* sprite = new Sprite(engine->getRenderer(), "resources/sprites/dish.bmp");

	Coordinate* fakeFloorPosition = new Coordinate(position->getX(), position->getY());
	DishFakeFloorEntity* fakeFloor = new DishFakeFloorEntity(this->engine, fakeFloorPosition);

	dish->addComponent(new RenderComponent(engine, dish, sprite));

	this->floors->push_back(fakeFloor);
	this->addEntity(dish);
}

void Game::addEnemy(Coordinate* position, EnemyType enemyType, double idleTime) {
	EnemyEntity* enemy = new EnemyEntity(this->engine, position, enemyType, idleTime, this->player, this->ingredients);

	this->setWalkingEntityColliders(enemy);
	this->enemies->push_back(enemy);
	this->addEntity(enemy);
}

void Game::addPlayer(Coordinate* position) {
	this->player->setInitialPosition(position);
}

void Game::ingredientFinished() {
	this->currentFinishedIngredients++;

	if (this->currentFinishedIngredients >= this->totalIngredients) {
		this->victory();
	}
}

void Game::pepperThrown() {
	this->pepper--;
}

void Game::playerDied() {
	this->lives--;

	if (this->lives <= 0) {
		this->input->setEnabled(false);
		this->gameOverText->setEnabled(true);
	}
	else {
		this->player->respawn();

		for (Entity* enemy : *this->enemies) {
			((EnemyEntity*)enemy)->respawn();
		}
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

int Game::getPepper() {
	return this->pepper;
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
	delete this->ingredients;
	delete this->enemies;

	delete this->previousFieldPosition;
}
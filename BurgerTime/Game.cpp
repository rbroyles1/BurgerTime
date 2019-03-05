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

Game::Game(Engine* engine) : Entity(engine) {
	this->entities = new std::vector<Entity*>();
	this->floors = new std::vector<Entity*>();
	this->leftFloorsLimits = new std::vector<Entity*>();
	this->rightFloorsLimits = new std::vector<Entity*>();
	this->stairs = new std::vector<Entity*>();
	this->upStairsLimits = new std::vector<Entity*>();
	this->downStairsLimits = new std::vector<Entity*>();
}

void Game::init() {
	this->engine->getMessageDispatcher()->subscribe(EXIT, this);

	this->createFpsCounter();
	this->createGameComponents();
	this->createStairs();
	this->createFloors();
	this->createFloorsLimits();
	this->createPlayerEntity();

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

void Game::createGameComponents() {
	this->addComponent(new InputComponent(this->engine, this));
}

void Game::createFpsCounter() {
	Entity* fpsCounter = new Entity(this->engine, new Coordinate(10, 10));
	Text* text = new Text(this->engine->getRenderer(), "space_invaders.ttf", 25);

	fpsCounter->addComponent(new FpsCounterComponent(this->engine, fpsCounter, text));
	this->addEntity(fpsCounter);
}

void Game::createPlayerEntity() {
	PlayerEntity* player = new PlayerEntity(this->engine, new Coordinate(100, 208));
	player->setPlayerColliders(this->floors, this->leftFloorsLimits, this->rightFloorsLimits, this->stairs, this->upStairsLimits, this->downStairsLimits);

	this->addEntity(player);
}

void Game::createFloors() {
	for (int i = 0; i < 5; i++) {
		Entity* floor = new Entity(this->engine, new Coordinate(66 + 16 * i, 216));
		Sprite* floorSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/floor.bmp");

		floor->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));
		floor->addComponent(new RenderComponent(this->engine, floor, floorSprite));

		this->floors->push_back(floor);
		this->addEntity(floor);
	}

	for (int i = 0; i < 5; i++) {
		Entity* floor = new Entity(this->engine, new Coordinate(90 + 16 * i, 168));
		Sprite* floorSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/floor.bmp");

		floor->setBoundingBox(new BoundingBox(new Coordinate(16, 3)));
		floor->addComponent(new RenderComponent(this->engine, floor, floorSprite));

		this->floors->push_back(floor);
		this->addEntity(floor);
	}
}

void Game::createFloorsLimits() {
	Entity* upLeftLimit = new Entity(this->engine, new Coordinate(74, 168));
	Entity* upRightLimit = new Entity(this->engine, new Coordinate(170, 168));
	Entity* downLeftLimit = new Entity(this->engine, new Coordinate(50, 216));
	Entity* downRightLimit = new Entity(this->engine, new Coordinate(146, 216));

	upLeftLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));
	upRightLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));
	downLeftLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));
	downRightLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));

	this->leftFloorsLimits->push_back(downLeftLimit);
	this->leftFloorsLimits->push_back(upLeftLimit);
	this->rightFloorsLimits->push_back(downRightLimit);
	this->rightFloorsLimits->push_back(upRightLimit);
}

void Game::createStairs() {
	for (int i = 0; i < 3; i++) {
		Entity* stair = new Entity(this->engine, new Coordinate(100, 207 - 16 * i));
		Sprite* stairSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/stairs.bmp");

		stair->setBoundingBox(new BoundingBox(new Coordinate(1, 16)));
		stair->addComponent(new RenderComponent(this->engine, stair, stairSprite));

		this->stairs->push_back(stair);
		this->addEntity(stair);
	}

	Entity* upStairLimit = new Entity(this->engine, new Coordinate(100, 151));
	upStairLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));

	Entity* downStairLimit = new Entity(this->engine, new Coordinate(100, 216));
	downStairLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 2)));

	this->upStairsLimits->push_back(upStairLimit);
	this->downStairsLimits->push_back(downStairLimit);
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
}
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
	this->leftFloorsLimits = new std::vector<Entity*>();
	this->rightFloorsLimits = new std::vector<Entity*>();
}

void Game::init() {
	this->engine->getMessageDispatcher()->subscribe(EXIT, this);

	this->createFpsCounter();
	this->createGameComponents();
	this->createPlayerEntity();
	this->createFloors();
	this->createFloorsLimits();
	this->createStairs();

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
	PlayerEntity* player = new PlayerEntity(this->engine, new Coordinate(100, 200), this->leftFloorsLimits, this->rightFloorsLimits);

	this->addEntity(player);
}

void Game::createFloors() {
	for (int i = 0; i < 5; i++) {
		Entity* floor = new Entity(this->engine, new Coordinate(66 + 16 * i, 216));
		Sprite* floorSprite = new Sprite(this->engine->getRenderer(), "resources/sprites/floor.bmp");

		floor->addComponent(new RenderComponent(this->engine, floor, floorSprite));
		this->addEntity(floor);
	}
}

void Game::createFloorsLimits() {
	Entity* leftLimit = new Entity(this->engine, new Coordinate(50, 200));
	Entity* rightLimit = new Entity(this->engine, new Coordinate(146, 200));

	leftLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	rightLimit->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));

	this->leftFloorsLimits->push_back(leftLimit);
	this->rightFloorsLimits->push_back(rightLimit);
}

void Game::createStairs() {
}

Game::~Game() {
	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		delete *it;
	}

	delete this->entities;
	delete this->leftFloorsLimits;
	delete this->rightFloorsLimits;
}
#include "Game.h"
#include "Engine.h"
#include "Entity.h"
#include "Text.h"
#include "FpsCounterComponent.h"
#include "InputComponent.h"
#include "BoxCollideComponent.h"
#include "PlayerEntity.h"

Game::Game(Engine* engine) : Entity(engine) {
	this->entities = new std::vector<Entity*>();
	this->colliders = new std::vector<BoxCollideComponent*>();
}

void Game::init() {
	this->createFpsCounter();
	this->createGameComponents();
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
	this->send(message);

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
	Entity* fpsCounter = new Entity(this->engine, Coordinate(10, 10));
	Text* text = new Text(this->engine->getRenderer(), "space_invaders.ttf", 25);

	fpsCounter->addComponent(new FpsCounterComponent(this->engine, fpsCounter, text));
	this->addEntity(fpsCounter);
}

void Game::createPlayerEntity() {
	PlayerEntity* player = new PlayerEntity(this->engine, Coordinate(24, 200));
	BoxCollideComponent* playerBox = new BoxCollideComponent(this->engine, player, new Coordinate(16, 16), FLOOR_BOUND_COLLISION, this->colliders);

	PlayerEntity* test = new PlayerEntity(this->engine, Coordinate(60, 200));
	BoxCollideComponent* testBox = new BoxCollideComponent(this->engine, test, new Coordinate(16, 16), FLOOR_BOUND_COLLISION, this->colliders);

	this->colliders->push_back(playerBox);
	this->colliders->push_back(testBox);

	player->addComponent(playerBox);
	test->addComponent(testBox);

	this->addReceiver(player);
	this->addEntity(player);
	this->addEntity(test);
}

Game::~Game() {
	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		delete *it;
	}

	delete this->entities;
	delete this->colliders;
}
#include "Game.h"
#include "Engine.h"
#include "Entity.h"
#include "Text.h"
#include "FpsCounterComponent.h"
#include "InputComponent.h"
#include "BoxCollideComponent.h"
#include "PlayerRigidBodyComponent.h"
#include "PlayerRenderComponent.h"

// TODO maybe make that only components can receive messages, not the entities
// TODO maybe create list of last received messages in the component class, that can be checked
// TODO maybe have BoxCollideComponent and BoxCollideDetectorComponent. The detector receives the entities, and gets the BoxCollideComponnent for each, to check for collisions
Game::Game(Engine* engine) : Entity(engine) {
	this->entities = new std::vector<Entity*>();
	this->leftFloorsLimitsColliders = new std::vector<BoxCollideComponent*>();
	this->rightFloorsLimitsColliders = new std::vector<BoxCollideComponent*>();
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
	Entity* fpsCounter = new Entity(this->engine, Coordinate(10, 10));
	Text* text = new Text(this->engine->getRenderer(), "space_invaders.ttf", 25);

	fpsCounter->addComponent(new FpsCounterComponent(this->engine, fpsCounter, text));
	this->addEntity(fpsCounter);
}

void Game::createPlayerEntity() {
	Entity* player = new Entity(this->engine, Coordinate(100, 200));

	PlayerRenderComponent* renderComponent = new PlayerRenderComponent(this->engine, player);
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, player);
	BoxCollideComponent* playerBoxLeft = new BoxCollideComponent(this->engine, player, new Coordinate(16, 16), LIMIT_LEFT, this->leftFloorsLimitsColliders);
	BoxCollideComponent* playerBoxRight = new BoxCollideComponent(this->engine, player, new Coordinate(16, 16), LIMIT_RIGHT, this->rightFloorsLimitsColliders);

	player->addComponent(renderComponent);
	player->addComponent(rigidBodyComponent);
	player->addComponent(playerBoxLeft);
	player->addComponent(playerBoxRight);

	this->addEntity(player);
}

void Game::createFloors() {
}

void Game::createFloorsLimits() {
	Entity* leftLimit = new Entity(this->engine, Coordinate(50, 200));
	Entity* rightLimit = new Entity(this->engine, Coordinate(150, 200));

	BoxCollideComponent* leftBox = new BoxCollideComponent(this->engine, leftLimit, new Coordinate(16, 16), LIMIT_LEFT, new std::vector<BoxCollideComponent*>());
	BoxCollideComponent* rightBox = new BoxCollideComponent(this->engine, rightLimit, new Coordinate(16, 16), LIMIT_RIGHT, new std::vector<BoxCollideComponent*>());

	leftLimit->addComponent(leftBox);
	rightLimit->addComponent(rightBox);

	this->leftFloorsLimitsColliders->push_back(leftBox);
	this->rightFloorsLimitsColliders->push_back(rightBox);
}

void Game::createStairs() {
}

Game::~Game() {
	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		delete *it;
	}

	delete this->entities;
	delete this->leftFloorsLimitsColliders;
	delete this->rightFloorsLimitsColliders;
}
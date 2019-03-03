#include "Game.h"
#include "Engine.h"
#include "Entity.h"
#include "Text.h"
#include "FpsCounterComponent.h"
#include "InputComponent.h"
#include "RenderComponent.h"
#include "PlayerRigidBodyComponent.h"

Game::Game(Engine* engine) {
	this->engine = engine;
	this->entities = new std::vector<Entity*>();
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
	Entity* fpsCounter = new Entity(Coordinate(10, 10));
	Text* text = new Text(this->engine->getRenderer(), "space_invaders.ttf", 25);

	fpsCounter->addComponent(new FpsCounterComponent(this->engine, fpsCounter, text));
	this->addEntity(fpsCounter);
}

void Game::createPlayerEntity() {
	Entity* player = new Entity(Coordinate(24, 200));
	PlayerRigidBodyComponent* rigidBodyComponent = new PlayerRigidBodyComponent(this->engine, player);
	RenderComponent* renderComponent = new RenderComponent(this->engine, player,
		new Sprite(this->engine->getRenderer(), "resources/sprites/cook (%d).bmp", 4, 6));

	player->addComponent(rigidBodyComponent);
	player->addComponent(renderComponent);

	this->addReceiver(rigidBodyComponent);
	this->addEntity(player);
}

Game::~Game() {
	for (auto it = this->entities->begin(); it != this->entities->end(); it++) {
		delete *it;
	}

	delete this->entities;
}
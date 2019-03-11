#include "PepperCounterComponent.h"

PepperCounterComponent::PepperCounterComponent(Engine* engine, Entity* entity, Game* game) : Component(engine, entity) {
	this->header = new Text(this->engine->getRenderer(), "space_invaders.ttf", 8);
	this->pepper = new Text(this->engine->getRenderer(), "space_invaders.ttf", 8);
	this->game = game;
}

void PepperCounterComponent::update(double dt) {
	Coordinate* headerPos = this->entity->getPosition();
	Coordinate* pepperPos = new Coordinate(headerPos->getX() + 2, headerPos->getY() + 8);
	std::string score = std::to_string(this->game->getPepper());

	this->header->draw(headerPos, "PEPPER", 0, 255, 0);
	this->pepper->draw(pepperPos, score.c_str());
}

PepperCounterComponent::~PepperCounterComponent() {
	delete this->header;
	delete this->pepper;
}

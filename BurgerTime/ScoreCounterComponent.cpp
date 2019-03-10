#include "ScoreCounterComponent.h"

ScoreCounterComponent::ScoreCounterComponent(Engine* engine, Entity* entity, Game* game) : Component(engine, entity) {
	this->header = new Text(this->engine->getRenderer(), "space_invaders.ttf", 8);
	this->score = new Text(this->engine->getRenderer(), "space_invaders.ttf", 8);
	this->game = game;
}

void ScoreCounterComponent::update(double dt) {
	Coordinate* headerPos = this->entity->getPosition();
	Coordinate* scorePos = new Coordinate(headerPos->getX() + 2, headerPos->getY() + 8);
	std::string score = std::to_string(this->game->getScore());

	this->header->draw(headerPos, "1UP", 255, 0, 0);
	this->score->draw(scorePos, score.c_str());
}

ScoreCounterComponent::~ScoreCounterComponent() {
	delete this->header;
	delete this->score;
}

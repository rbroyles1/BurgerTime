#include "LivesTrackerEntity.h"
#include "Constants.h"

LivesTrackerEntity::LivesTrackerEntity(Engine* engine, Coordinate* position, Game* game) : Entity(engine, position) {
	this->sprites = new std::vector<RenderComponent*>();
	this->game = game;

	Sprite* sprite = new Sprite(engine->getRenderer(), "resources/sprites/life.bmp");

	for (int i = 0; i < MAX_LIVES; i++) {
		this->sprites->push_back(new RenderComponent(engine, this, sprite, new Coordinate(0, -8 * i)));
	}
}

void LivesTrackerEntity::update(double dt) {
	Entity::update(dt);

	for (int i = 0; i < game->getLives() && i < MAX_LIVES; i++) {
		this->sprites->at(i)->update(dt);
	}
}

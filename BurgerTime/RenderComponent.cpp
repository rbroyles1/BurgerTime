#include "RenderComponent.h"

RenderComponent::RenderComponent(Engine* engine, Entity* entity, Sprite* sprite) : RenderComponent(engine, entity, sprite, new Coordinate(0, 0)) { }

RenderComponent::RenderComponent(Engine * engine, Entity * entity, Sprite * sprite, Coordinate * offset) : Component(engine, entity) {
	this->sprite = sprite;
	this->offset = offset;
}

void RenderComponent::update(double dt) {
	this->sprite->draw(entity->getPosition()->getX() + offset->getX(), 
		entity->getPosition()->getY() + offset->getY(), dt);
}

RenderComponent::~RenderComponent() {
	delete this->sprite;
}
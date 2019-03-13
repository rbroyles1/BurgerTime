#include "RenderComponent.h"

RenderComponent::RenderComponent(Engine* engine, Entity* entity, Sprite* sprite) : RenderComponent(engine, entity, sprite, new Coordinate(0, 0)) { }

RenderComponent::RenderComponent(Engine * engine, Entity * entity, Sprite * sprite, Coordinate * offset) : Component(engine, entity) {
	this->sprite = sprite;
	this->offset = offset;
}

void RenderComponent::update(double dt) {
	this->sprite->draw((int)entity->getPosition()->getX() + (int)offset->getX(),
		(int)entity->getPosition()->getY() + (int)offset->getY(), dt);
}

Sprite* RenderComponent::getSprite() {
	return this->sprite;
}

RenderComponent::~RenderComponent() {
	delete this->sprite;
}
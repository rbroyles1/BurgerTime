#include "RenderComponent.h"

RenderComponent::RenderComponent(Engine* engine, Entity* entity, Sprite* sprite) : Component(engine, entity) {
	this->sprite = sprite;
}

void RenderComponent::update(double dt) {
	this->sprite->draw(entity->getPosition()->x, entity->getPosition()->y);
}
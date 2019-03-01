#include "FpsCounterComponent.h"
#include "Engine.h"

FpsCounterComponent::FpsCounterComponent(Engine* engine, Entity* entity, Text* text) : Component(engine, entity) {
	this->text = text;
}

void FpsCounterComponent::update(double dt) {
	std::string message = std::to_string(engine->getFrameRate());
	this->text->draw(this->entity->getPosition(), message.c_str());
}

FpsCounterComponent::~FpsCounterComponent() {
	delete text;
}
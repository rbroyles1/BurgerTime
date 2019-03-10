#include "InputComponent.h"
#include "Engine.h"

InputComponent::InputComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->enabled = true;
}

void InputComponent::update(double dt) {
	if (this->enabled) {
		if (engine->getKeyStatus(SDLK_ESCAPE) || engine->getKeyStatus(SDLK_q)) this->engine->getMessageDispatcher()->send(EXIT);

		if (engine->getKeyStatus(SDLK_a) || engine->getKeyStatus(SDLK_LEFT)) this->engine->getMessageDispatcher()->send(MOVE_LEFT);
		if (engine->getKeyStatus(SDLK_d) || engine->getKeyStatus(SDLK_RIGHT)) this->engine->getMessageDispatcher()->send(MOVE_RIGHT);
		if (engine->getKeyStatus(SDLK_w) || engine->getKeyStatus(SDLK_UP)) this->engine->getMessageDispatcher()->send(MOVE_UP);
		if (engine->getKeyStatus(SDLK_s) || engine->getKeyStatus(SDLK_DOWN)) this->engine->getMessageDispatcher()->send(MOVE_DOWN);
	}
}

void InputComponent::setEnabled(bool enabled) {
	this->enabled = enabled;
}

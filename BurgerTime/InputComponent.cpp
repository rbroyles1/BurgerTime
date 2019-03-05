#include "InputComponent.h"
#include "Engine.h"

InputComponent::InputComponent(Engine* engine, Entity* entity) : Component(engine, entity) { }

void InputComponent::update(double dt) {
	if (engine->getKeyStatus(SDLK_ESCAPE) || engine->getKeyStatus(SDLK_q)) this->engine->getMessageDispatcher()->send(EXIT);

	if (engine->getKeyStatus(SDLK_a) || engine->getKeyStatus(SDLK_LEFT)) this->engine->getMessageDispatcher()->send(MOVE_LEFT);
	if (engine->getKeyStatus(SDLK_d) || engine->getKeyStatus(SDLK_RIGHT)) this->engine->getMessageDispatcher()->send(MOVE_RIGHT);
}
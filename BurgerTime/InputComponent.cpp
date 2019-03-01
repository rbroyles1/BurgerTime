#include "InputComponent.h"
#include "Engine.h"

InputComponent::InputComponent(Engine* engine, Entity* entity) : Component(engine, entity) { }

void InputComponent::update(double dt) {
	if (engine->getKeyStatus(SDLK_ESCAPE) || engine->getKeyStatus(SDLK_q)) this->entity->receive(EXIT);

	if (engine->getKeyStatus(SDLK_a) || engine->getKeyStatus(SDLK_LEFT)) this->entity->receive(MOVE_LEFT);
	if (engine->getKeyStatus(SDLK_d) || engine->getKeyStatus(SDLK_RIGHT)) this->entity->receive(MOVE_RIGHT);
}
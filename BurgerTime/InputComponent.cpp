#include "InputComponent.h"
#include "Engine.h"

InputComponent::InputComponent(Engine* engine, Entity* entity) : Component(engine, entity) { }

void InputComponent::update(float dt) {
	if (engine->getKeyStatus(SDLK_ESCAPE) || engine->getKeyStatus(SDLK_q)) {
		engine->stop();
		return;
	}
}
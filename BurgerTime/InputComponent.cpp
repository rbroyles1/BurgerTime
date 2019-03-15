#include "InputComponent.h"
#include "Engine.h"
#include "Constants.h"

InputComponent::InputComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->enabled = true;
}

void InputComponent::update(double dt) {
	if (this->enabled) {
		if (engine->getKeyStatus(SDLK_ESCAPE) || engine->getKeyStatus(SDLK_q)) this->engine->getMessageDispatcher()->send(EXIT);

		if (engine->getKeyStatus(SDLK_w) || engine->getKeyStatus(SDLK_UP) || engine->getControllerStatus(CONTROLLER_UP)) this->engine->getMessageDispatcher()->send(MOVE_UP);
		if (engine->getKeyStatus(SDLK_a) || engine->getKeyStatus(SDLK_LEFT) || engine->getControllerStatus(CONTROLLER_LEFT)) this->engine->getMessageDispatcher()->send(MOVE_LEFT);
		if (engine->getKeyStatus(SDLK_s) || engine->getKeyStatus(SDLK_DOWN) || engine->getControllerStatus(CONTROLLER_DOWN)) this->engine->getMessageDispatcher()->send(MOVE_DOWN);
		if (engine->getKeyStatus(SDLK_d) || engine->getKeyStatus(SDLK_RIGHT) || engine->getControllerStatus(CONTROLLER_RIGHT)) this->engine->getMessageDispatcher()->send(MOVE_RIGHT);

		
		if (engine->getKeyStatus(SDLK_SPACE) || engine->getControllerStatus(0) || engine->getControllerStatus(1) || engine->getControllerStatus(2) || engine->getControllerStatus(3)) {
			this->engine->getMessageDispatcher()->send(MAIN_ACTION);
		}
	}
}

void InputComponent::onKeyDown(SDL_Keycode key) {
	if (key == SDLK_n) this->engine->getMessageDispatcher()->send(SWITCH_NIGHT_MODE);
	if (key == SDLK_l) this->engine->getMessageDispatcher()->send(LOAD_NEW_LEVEL);
	if (key == SDLK_r) this->engine->getMessageDispatcher()->send(RESET_GAME);
}

void InputComponent::onKeyUp(SDL_Keycode key) { }

void InputComponent::onControllerDown(Uint8 button) {
	if (button == 4) this->engine->getMessageDispatcher()->send(SWITCH_NIGHT_MODE);
	if (button == 7) this->engine->getMessageDispatcher()->send(LOAD_NEW_LEVEL);
	if (button == 5) this->engine->getMessageDispatcher()->send(RESET_GAME);
}

void InputComponent::onControllerUp(Uint8 button) {

}

void InputComponent::setEnabled(bool enabled) {
	this->enabled = enabled;
}

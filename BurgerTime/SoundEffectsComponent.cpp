#include "SoundEffectsComponent.h"
#include "Engine.h"

SoundEffectsComponent::SoundEffectsComponent(Engine* engine, Entity* entity) : Component(engine, entity) {
	this->pepper = Mix_LoadWAV("resources/sounds/loose.mp3");

	this->performSubscriptions();
}

void SoundEffectsComponent::update(double dt) {
	if (this->hasReceived(PEPPER_THROWN)) {
		Mix_PlayChannel(-1, this->pepper, 0);
	}

	this->clearMessages();
}

void SoundEffectsComponent::performSubscriptions() {
	this->engine->getMessageDispatcher()->subscribe(PEPPER_THROWN, this);
}

SoundEffectsComponent::~SoundEffectsComponent() {

}
#pragma once
#include "Component.h"
#include <SDL_mixer.h>

class SoundEffectsComponent : public Component {
	Mix_Chunk *pepper;

public:
	SoundEffectsComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);

	~SoundEffectsComponent();

private:
	void performSubscriptions();
};


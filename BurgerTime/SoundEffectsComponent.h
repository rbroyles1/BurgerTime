#pragma once
#include "Component.h"
#include <SDL_mixer.h>

class SoundEffectsComponent : public Component {
	Mix_Chunk *pepper;
	Mix_Chunk *ingredientStep;
	Mix_Chunk *ingredientHit;
	Mix_Chunk *squashed;

public:
	SoundEffectsComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);

	~SoundEffectsComponent();

private:
	void performSubscriptions();
};


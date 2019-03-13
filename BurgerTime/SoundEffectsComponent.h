#pragma once
#include "Component.h"
#include <SDL_mixer.h>

class SoundEffectsComponent : public Component {
	Mix_Music* backgroundMusic;

	Mix_Chunk* intro;
	Mix_Chunk* loose;

	Mix_Chunk *pepper;
	Mix_Chunk *ingredientStep;
	Mix_Chunk *ingredientHit;
	Mix_Chunk *squashed;

	bool dying;

public:
	SoundEffectsComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);

	~SoundEffectsComponent();

private:
	void performSubscriptions();
};


#pragma once
#include "SDL.h"

class Sprite {
	SDL_Renderer * renderer;
	SDL_Texture * texture;

public:
	Sprite(SDL_Renderer* renderer, const char* spritePath);

	void draw(int x, int y);

	~Sprite();
};
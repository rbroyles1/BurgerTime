#pragma once
#include "SDL.h"

class Sprite {
	SDL_Renderer * renderer;
	SDL_Texture * texture;

public:
	Sprite(SDL_Renderer * renderer, SDL_Texture * texture);
	void draw(int x, int y);
	void destroy();
};
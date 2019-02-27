#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Sprite {
	SDL_Renderer * renderer;
	SDL_Texture * texture;

public:
	Sprite(SDL_Renderer * renderer, SDL_Texture * texture) {
		this->renderer = renderer;
		this->texture = texture;
	}

	void draw(int x, int y) {
		SDL_Rect spritePosition;

		spritePosition.x = x;
		spritePosition.y = y;

		SDL_QueryTexture(this->texture, nullptr, nullptr, &spritePosition.w, &spritePosition.h);
		SDL_RenderCopy(this->renderer, this->texture, nullptr, &spritePosition);
	}

	void destroy() {
		SDL_DestroyTexture(this->texture);
	}
};
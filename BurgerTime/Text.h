#pragma once
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"

class Text {
	SDL_Renderer* renderer;
	TTF_Font* font;

public:
	Text(SDL_Renderer* renderer, const char* fontPath, int fontSize) {
		this->renderer = renderer;
		this->font = TTF_OpenFont(fontPath, fontSize);
	}

	void draw(Coordinate* coordinate, const char *message) {
		SDL_Surface* surface = TTF_RenderText_Solid(this->font, message, { 255, 255, 255 });
		SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);

		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
		SDL_Rect dstrect = { coordinate->x, coordinate->y, texW, texH };

		SDL_RenderCopy(this->renderer, texture, nullptr, &dstrect);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}

	~Text() {
		TTF_CloseFont(this->font);
	}
};
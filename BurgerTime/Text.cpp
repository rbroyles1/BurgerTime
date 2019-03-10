#include "Text.h"
#include "Constants.h"

Text::Text(SDL_Renderer* renderer, const char* fontPath, int fontSize) {
	this->renderer = renderer;
	this->font = TTF_OpenFont(fontPath, fontSize);
}

void Text::draw(Coordinate* coordinate, const char *message, Uint8 red, Uint8 green, Uint8 blue) {
	SDL_Surface* surface = TTF_RenderText_Solid(this->font, message, { red, green, blue });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
	SDL_Rect dstrect = { coordinate->getX() * RESOLUTION_MULTIPLIER, coordinate->getY() * RESOLUTION_MULTIPLIER,
		texW * RESOLUTION_MULTIPLIER, texH * RESOLUTION_MULTIPLIER};

	SDL_RenderCopy(this->renderer, texture, nullptr, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

Text::~Text() {
	TTF_CloseFont(this->font);
}
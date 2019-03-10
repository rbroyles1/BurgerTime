#pragma once
#include <string>
#include "SDL_ttf.h"
#include "Coordinate.h"

class Text {
	SDL_Renderer* renderer;
	TTF_Font* font;

public:
	Text(SDL_Renderer* renderer, const char* fontPath, int fontSize);
	void draw(Coordinate* coordinate, const char *message, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);
	~Text();
};
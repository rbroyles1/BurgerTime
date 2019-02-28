#pragma once
#include <string>
#include "SDL_ttf.h"
#include "Coordinate.h"

class Text {
	SDL_Renderer* renderer;
	TTF_Font* font;

public:
	Text(SDL_Renderer* renderer, const char* fontPath, int fontSize);
	void draw(Coordinate* coordinate, const char *message);
	~Text();
};
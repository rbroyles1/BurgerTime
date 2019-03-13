#pragma once
#include <vector>
#include "SDL.h"
#include "Constants.h"

class Sprite {
	SDL_Renderer * renderer;
	std::vector<SDL_Texture*>* textures;
	int millisecsPerFrame;
	double timeElapsed;

public:
	Sprite(SDL_Renderer* renderer, const char* spritePath);
	Sprite(SDL_Renderer* renderer, const char* spritePattern, int indexStart, int indexEnd, int millisecsPerFrame);

	void draw(int x, int y, double dt);
	void resetAnimation();

	~Sprite();
};
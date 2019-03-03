#include "Sprite.h"
#include "Constants.h"

Sprite::Sprite(SDL_Renderer* renderer, const char* spritePath) : Sprite(renderer, spritePath, 0, 0, 0) {}

Sprite::Sprite(SDL_Renderer * renderer, const char* spritePattern, int indexStart, int indexEnd, int millisecsPerFrame) {
	this->renderer = renderer;
	this->textures = new std::vector<SDL_Texture*>();
	this->millisecsPerFrame = millisecsPerFrame;
	this->millisecsElapsed = 0;
	
	for (int i = indexStart; i <= indexEnd; i++) {
		char spritePath[1000];
		snprintf(spritePath, 1000, spritePattern, i);

		SDL_Surface* spriteSurface = SDL_LoadBMP(spritePath);
		this->textures->push_back(SDL_CreateTextureFromSurface(this->renderer, spriteSurface));

		SDL_FreeSurface(spriteSurface);
	}
}

void Sprite::draw(int x, int y, double dt) {
	SDL_Rect spritePosition;
	spritePosition.x = x;
	spritePosition.y = y;

	int frameIndex = this->millisecsPerFrame > 0 ? (this->millisecsElapsed / this->millisecsPerFrame) % this->textures->size() : 0;
	SDL_Texture* texture = this->textures->at(frameIndex);

	SDL_QueryTexture(texture, nullptr, nullptr, &spritePosition.w, &spritePosition.h);

	spritePosition.w *= RESOLUTION_MULTIPLIER;
	spritePosition.h *= RESOLUTION_MULTIPLIER;

	SDL_RenderCopy(this->renderer, texture, nullptr, &spritePosition);

	this->millisecsElapsed += dt * 1000;
}

void Sprite::resetAnimation() {
	this->millisecsElapsed = 0;
}

Sprite::~Sprite() {
	for (auto i = this->textures->begin(); i != this->textures->end(); i++) {
		SDL_DestroyTexture(*i);
	}

	delete this->textures;
}
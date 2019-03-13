#include "Sprite.h"
#include "Constants.h"

Sprite::Sprite(SDL_Renderer* renderer, const char* spritePath) : Sprite(renderer, spritePath, 0, 0, 0) {}

Sprite::Sprite(SDL_Renderer * renderer, const char* spritePattern, int indexStart, int indexEnd, int millisecsPerFrame) {
	this->renderer = renderer;
	this->textures = new std::vector<SDL_Texture*>();
	this->millisecsPerFrame = millisecsPerFrame;
	this->timeElapsed = 0;
	
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

	int frameIndex = this->millisecsPerFrame > 0 ? ((int)(this->timeElapsed * 1000) / this->millisecsPerFrame) % this->textures->size() : 0;
	SDL_Texture* texture = this->textures->at(frameIndex);

	SDL_QueryTexture(texture, nullptr, nullptr, &spritePosition.w, &spritePosition.h);

	spritePosition.w *= RESOLUTION_MULTIPLIER;
	spritePosition.h *= RESOLUTION_MULTIPLIER;
	spritePosition.x = x * RESOLUTION_MULTIPLIER - spritePosition.w / 2;
	spritePosition.y = y * RESOLUTION_MULTIPLIER - spritePosition.h / 2;

	SDL_RenderCopy(this->renderer, texture, nullptr, &spritePosition);

	this->timeElapsed += dt;
}

void Sprite::resetAnimation() {
	this->timeElapsed = 0;
}

Sprite::~Sprite() {
	for (auto i = this->textures->begin(); i != this->textures->end(); i++) {
		SDL_DestroyTexture(*i);
	}

	delete this->textures;
}
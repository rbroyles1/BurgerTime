#include "Sprite.h"
#include "Constants.h"

Sprite::Sprite(SDL_Renderer* renderer, const char* spritePath) {
	SDL_Surface* spriteSurface = SDL_LoadBMP(spritePath);
	
	this->renderer = renderer;
	this->texture = SDL_CreateTextureFromSurface(this->renderer, spriteSurface);

	SDL_FreeSurface(spriteSurface);
}

void Sprite::draw(int x, int y) {
	SDL_Rect spritePosition;

	spritePosition.x = x;
	spritePosition.y = y;

	SDL_QueryTexture(this->texture, nullptr, nullptr, &spritePosition.w, &spritePosition.h);

	spritePosition.w *= RESOLUTION_MULTIPLIER;
	spritePosition.h *= RESOLUTION_MULTIPLIER;

	SDL_RenderCopy(this->renderer, this->texture, nullptr, &spritePosition);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(this->texture);
}
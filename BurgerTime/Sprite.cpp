#include "Sprite.h"

Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture) {
	this->renderer = renderer;
	this->texture = texture;
}

void Sprite::draw(int x, int y) {
	SDL_Rect spritePosition;

	spritePosition.x = x;
	spritePosition.y = y;

	SDL_QueryTexture(this->texture, nullptr, nullptr, &spritePosition.w, &spritePosition.h);
	SDL_RenderCopy(this->renderer, this->texture, nullptr, &spritePosition);
}

void Sprite::destroy() {
	SDL_DestroyTexture(this->texture);
}
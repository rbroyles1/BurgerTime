#include "avancezlib.h"
#include <iostream>
#include <chrono>
#include <thread>

void AvancezLib::destroy() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	TTF_CloseFont(this->font);
	
	TTF_Quit();
	SDL_Quit();
}

bool AvancezLib::init(int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0) {
		return false;
	}

	this->window = SDL_CreateWindow("Lab 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->font = TTF_OpenFont("space_invaders.ttf", 25);

	this->millisecondsPerFrame = 0;
	this->previousFrameEndTime = 0;
	this->previousUpdateTime = 0;
	this->keepRendering = true;

	return true;
}

bool AvancezLib::update() {
	int current = this->getElapsedTime();
	int delta = current - this->previousUpdateTime;
	this->previousUpdateTime = current;

	this->handleEvents();

	SDL_RenderClear(this->renderer);

	/*for (int i = 0; i < this->entities.size(); i++) {
		this->entities[i]->update(delta);
	}*/
	
	SDL_RenderPresent(this->renderer);
	this->fpsLimitSleep();

	return this->keepRendering;
}

void AvancezLib::stop() {
	this->keepRendering = false;
}

void AvancezLib::drawText(int x, int y, const char* msg) {
	SDL_Surface* surface = TTF_RenderText_Solid(this->font, msg, { 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
	SDL_Rect dstrect = { x, y, texW, texH };

	SDL_RenderCopy(this->renderer, texture, nullptr, &dstrect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

/*void AvancezLib::addEntity(Sprite * sprite) {
	this->entities.push_back(sprite);
}*/

void AvancezLib::setFpsLimit(int limit) {
	this->millisecondsPerFrame = 1000 / limit;
}

int AvancezLib::getElapsedTime() {
	return SDL_GetTicks();
}

int AvancezLib::getFrameRate() {
	return this->frameRate;
}

bool AvancezLib::getKeyStatus(SDL_Keycode key) {
	auto found = this->keyStatus.find(key);

	if (found != this->keyStatus.end()) {
		return found->second;
	}

	return false;
}

void AvancezLib::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:			
			this->keyStatus[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			this->keyStatus[event.key.keysym.sym] = false;
			break;
		case SDL_QUIT:
			this->stop();
			break;
		}
	}
}

void AvancezLib::fpsLimitSleep() {
	int sleepTime = this->millisecondsPerFrame - getElapsedTime() + this->previousFrameEndTime;

	if (sleepTime > 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
	}

	int delta = getElapsedTime() - this->previousFrameEndTime;
	this->frameRate = delta != 0? 1000 / delta : 1000;

	this->previousFrameEndTime = getElapsedTime();
}
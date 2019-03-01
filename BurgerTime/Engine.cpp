#include "Engine.h"
#include "SDL_ttf.h"
#include <chrono>
#include <thread>

bool Engine::init(Game* game, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0) {
		return false;
	}

	this->window = SDL_CreateWindow("Lab 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);

	this->millisecondsPerFrame = 0;
	this->previousFrameEndTime = 0;
	this->previousUpdateTime = 0;
	this->keepRendering = true;
	this->game = game;

	this->game->init();

	return true;
}


bool Engine::update() {
	int current = this->getElapsedTime();
	int delta = current - this->previousUpdateTime;
	this->previousUpdateTime = current;

	this->handleEvents();

	SDL_RenderClear(this->renderer);

	this->game->update(delta / 1000.0);

	SDL_RenderPresent(this->renderer);
	this->fpsLimitSleep();

	return this->keepRendering;
}

void Engine::stop() {
	this->keepRendering = false;
}

void Engine::setFpsLimit(int limit) {
	this->millisecondsPerFrame = 1000 / limit;
}

int Engine::getElapsedTime() {
	return SDL_GetTicks();
}

int Engine::getFrameRate() {
	return this->frameRate;
}

bool Engine::getKeyStatus(SDL_Keycode key) {
	auto found = this->keyStatus.find(key);

	if (found != this->keyStatus.end()) {
		return found->second;
	}

	return false;
}

SDL_Renderer* Engine::getRenderer() {
	return this->renderer;
}

void Engine::handleEvents() {
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

void Engine::fpsLimitSleep() {
	int sleepTime = this->millisecondsPerFrame - getElapsedTime() + this->previousFrameEndTime;

	if (sleepTime > 0) {
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
	}

	int delta = getElapsedTime() - this->previousFrameEndTime;
	this->frameRate = delta != 0 ? 1000 / delta : 1000;

	this->previousFrameEndTime = getElapsedTime();
}

Engine::~Engine() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	TTF_Quit();
	SDL_Quit();
}
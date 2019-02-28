#pragma once
#include <map>
#include "SDL.h"
#include "Entity.h"
#include "Game.h"

class Game;

class Engine {
	SDL_Window * window;
	SDL_Renderer * renderer;
	Game* game;
	std::map<SDL_Keycode, bool> keyStatus;

	int millisecondsPerFrame;
	int previousFrameEndTime;
	int previousUpdateTime;
	int frameRate;
	bool keepRendering;

public:
	bool init(Game* game, int width, int height);
	bool update();
	void stop();
	void setFpsLimit(int limit);
	int getElapsedTime();
	int getFrameRate();
	bool getKeyStatus(SDL_Keycode key);
	SDL_Renderer* getRenderer();
	void destroy();

private:
	void handleEvents();
	void fpsLimitSleep();
};
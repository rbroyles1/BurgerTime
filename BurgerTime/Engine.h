#pragma once
#include <map>
#include "SDL.h"
#include "MessageDispatcher.h"
#include "Receiver.h"
#include "Entity.h"
#include "Game.h"

class Game;

class Engine {
	Game* game;
	SDL_Window * window;
	SDL_Renderer * renderer;
	MessageDispatcher* messageDispatcher;
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
	MessageDispatcher* getMessageDispatcher();

	~Engine();

private:
	void handleEvents();
	void fpsLimitSleep();
};
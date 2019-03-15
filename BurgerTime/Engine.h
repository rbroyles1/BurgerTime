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
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Joystick* joystick;
	MessageDispatcher* messageDispatcher;
	std::map<SDL_Keycode, bool> keyStatus;
	std::map<Uint8, bool> controllerStatus;

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
	bool getControllerStatus(Uint8 button);
	SDL_Renderer* getRenderer();
	MessageDispatcher* getMessageDispatcher();

	~Engine();

private:
	void handleEvents();
	void fpsLimitSleep();
};
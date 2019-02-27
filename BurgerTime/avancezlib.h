#pragma once

#include <vector>
#include <map>
#include "SDL.h"
#include "SDL_ttf.h"

class AvancezLib {
	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font * font;
	//std::vector<Sprite*> entities;
	std::map<SDL_Keycode, bool> keyStatus;

	int millisecondsPerFrame;
	int previousFrameEndTime;
	int previousUpdateTime;
	int frameRate;
	bool keepRendering;

public:
	void destroy();
	bool init(int width, int height);
	bool update();
	void stop();
	void drawText(int x, int y, const char* msg); // TODO eliminate this
	//void addEntity(Sprite* sprite);
	void setFpsLimit(int limit);
	int getElapsedTime();
	int getFrameRate();
	bool getKeyStatus(SDL_Keycode key);

private:
	void handleEvents();
	void fpsLimitSleep();
};
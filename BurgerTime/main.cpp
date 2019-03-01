#include <string>
#include "Engine.h"
#include "Game.h"
#include "Constants.h"

int main(int argc, char* argv[]) {
	Engine engine;
	Game* game = new Game(&engine);

	if (engine.init(game, ORIGINAL_WIDTH * RESOLUTION_MULTIPLIER, ORIGINAL_HEIGHT * RESOLUTION_MULTIPLIER)) {
		engine.setFpsLimit(60);
		while (engine.update());
	}
	
	delete game;
	
	return 0;
}
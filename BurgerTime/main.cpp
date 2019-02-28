#include <string>
#include "Engine.h"
#include "Game.h"

int main(int argc, char* argv[]) {
	Engine engine;
	Game* game = new Game(&engine);

	if (engine.init(game, 512, 512)) {
		engine.setFpsLimit(60);
		while (engine.update());
	}
	
	delete game;
	
	return 0;
}
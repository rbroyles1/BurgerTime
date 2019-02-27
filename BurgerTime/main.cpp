#include <string>
#include "Engine.h"

void processInput(Engine& engine);

int main(int argc, char* argv[]) {
	Engine engine;

	engine.init(512, 512);
	engine.setFpsLimit(60);
	
	while (engine.update()) {
		processInput(engine);
		engine.drawText(25, 25, std::to_string(engine.getFrameRate()).c_str());
	}
	
	engine.destroy();
	
	return 0;
}

// TODO remove this
void processInput(Engine& engine) {
	if (engine.getKeyStatus(SDLK_ESCAPE) || engine.getKeyStatus(SDLK_q)) {
		engine.stop();
		return;
	}
	
	if (engine.getKeyStatus(SDLK_LEFT)) SDL_Log("LEFT\n");
	if (engine.getKeyStatus(SDLK_RIGHT)) SDL_Log("RIGHT\n");
	if (engine.getKeyStatus(SDLK_SPACE)) SDL_Log("FIRE!\n");
}
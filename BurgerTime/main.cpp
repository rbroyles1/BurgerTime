#include <string>
#include <vector>
#include <Windows.h>
#include "Engine.h"
#include "Game.h"
#include "Constants.h"

std::vector<std::string> listLevels() {
	std::vector<std::string> names;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile("resources/levels/*.*", &fd);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	return names;
}

std::string* chooseLevel() {
	std::vector<std::string> levels = listLevels();
	SDL_MessageBoxButtonData* buttons = new SDL_MessageBoxButtonData[levels.size()]();

	for (int i = 0; i < levels.size(); i++) {
		buttons[i] = { 0, i, levels.at(i).c_str() };
	}

	SDL_MessageBoxData messageBoxData = { SDL_MESSAGEBOX_INFORMATION, nullptr, "BurgerTime", "Choose a level", levels.size(), buttons, nullptr };

	int buttonId;

	if (SDL_ShowMessageBox(&messageBoxData, &buttonId) < 0 || buttonId < 0) {
		return nullptr;
	}

	return new std::string(std::string("resources/levels/") + std::string(buttons[buttonId].text));
}

int main(int argc, char* argv[]) {
	Engine engine;
	std::string* chosenLevel = chooseLevel();

	if (chosenLevel != nullptr) {
		Game* game = new Game(&engine, chosenLevel);

		if (engine.init(game, ORIGINAL_WIDTH * RESOLUTION_MULTIPLIER, ORIGINAL_HEIGHT * RESOLUTION_MULTIPLIER)) {
			engine.setFpsLimit(60);
			while (engine.update());
		}

		delete game;
	}
	
	return 0;
}
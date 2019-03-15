#pragma once
#include "SDL.h"
#include "Component.h"

class InputComponent : public Component {
	bool enabled;

public:
	InputComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);

	void onKeyDown(SDL_Keycode key);
	void onKeyUp(SDL_Keycode key);
	void onControllerDown(Uint8 button);
	void onControllerUp(Uint8 button);

	void setEnabled(bool enabled);
};


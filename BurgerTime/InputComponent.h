#pragma once
#include "Component.h"

class InputComponent : public Component {

public:
	InputComponent(Engine* engine, Entity* entity);

	virtual void update(float dt);
};


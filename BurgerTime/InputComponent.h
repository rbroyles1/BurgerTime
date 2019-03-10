#pragma once
#include "Component.h"

class InputComponent : public Component {
	bool enabled;

public:
	InputComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);
	void setEnabled(bool enabled);
};


#pragma once
#include <string>
#include "Component.h"
#include "Entity.h"
#include "Text.h"

class FpsCounterComponent : public Component {
	Text* text;

public:
	FpsCounterComponent(Engine* engine, Entity* entity, Text* text);

	virtual void update(float dt);

	virtual ~FpsCounterComponent();
};
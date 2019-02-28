#pragma once
#include <string>
#include "Component.h"
#include "Entity.h"
#include "Text.h"

class FpsCounterComponent : public Component {
	Text* text;

public:
	FpsCounterComponent(Engine* engine, Entity* entity, Text* text) : Component(engine, entity) {
		this->text = text;
	}

	virtual void update(float dt) {
		const char* message = /*std::to_string(engine->getFrameRate()).c_str()*/ "60";
		this->text->draw(this->entity->getPosition(), message);
	}

	virtual ~FpsCounterComponent() {
		Component::~Component();
		delete text;
	}
};
#pragma once
#include "Component.h"
#include "Text.h"

class TextRenderComponent : public Component {
	Text* text;
	std::string* message;

public:
	TextRenderComponent(Engine* engine, Entity* entity, std::string* message, Text* text);

	virtual void update(double dt);

	~TextRenderComponent();
};


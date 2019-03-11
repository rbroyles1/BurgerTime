#include "TextRenderComponent.h"

TextRenderComponent::TextRenderComponent(Engine* engine, Entity* entity, std::string* message, Text* text) : Component(engine, entity) {
	this->text = text;
	this->message = message;
}

void TextRenderComponent::update(double dt) {
	Coordinate* backgroundPosition = new Coordinate(entity->getPosition()->getX() + 1, entity->getPosition()->getY() + 1);

	this->text->draw(backgroundPosition, this->message->c_str(), 0, 0, 0);
	this->text->draw(entity->getPosition(), this->message->c_str());
}

TextRenderComponent::~TextRenderComponent() {
	delete this->text;
	delete this->message;
}

#include "DishFakeFloorEntity.h"
#include "RenderComponent.h"
#include "Engine.h"

DishFakeFloorEntity::DishFakeFloorEntity(Engine* engine, Coordinate* position) : Entity(engine, position) {
	this->setBoundingBox(new BoundingBox(new Coordinate(32, 2)));
}

void DishFakeFloorEntity::receive(Message message) {
	if (message == INGREDIENT_ON_FLOOR) {
		Coordinate* position = this->getPosition();
		position->setY(position->getY() - 8);

		this->engine->getMessageDispatcher()->send(INGREDIENT_FINISHED);
	}
}
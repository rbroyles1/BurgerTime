#include "PepperReloadEntity.h"
#include "Engine.h"
#include "BoxCollideComponent.h"

PepperReloadEntity::PepperReloadEntity(Engine* engine, Entity* player, std::vector<Entity*>* stairs) : Entity(engine) {
	std::vector<Entity*>* playerWrapper = new std::vector<Entity*>();
	
	this->stairs = stairs;

	this->iceCream = new Sprite(engine->getRenderer(), "resources/sprites/ice_cream.bmp");
	this->fries = new Sprite(engine->getRenderer(), "resources/sprites/fries.bmp");
	this->render = new RenderComponent(engine, this, this->iceCream);

	playerWrapper->push_back(player);

	this->addComponent(this->render);
	this->addComponent(new BoxCollideComponent(engine, this, INTERSECT_RELOAD_PEPPER, playerWrapper));

	this->setBoundingBox(new BoundingBox(new Coordinate(16, 16)));
	
	this->hide();
}

void PepperReloadEntity::update(double dt) {
	Entity::update(dt);

	if (this->timeTillSpawn > 0) {
		this->timeTillSpawn -= dt;

		if (this->timeTillSpawn <= 0) {
			this->show();
		}
	}

	if (this->hasReceived(INTERSECT_RELOAD_PEPPER)) {
		this->hide();
		this->engine->getMessageDispatcher()->send(INCREASE_PEPPER);
	}

	this->clearMessages();
}

void PepperReloadEntity::show() {
	Entity* stair = this->stairs->at(rand() % this->stairs->size());

	this->setPosition(*stair->getPosition());
	this->setEnabled(true);

	if (rand() % 2 == 0) {
		this->render->setSprite(this->iceCream);
	}
	else {
		this->render->setSprite(this->fries);
	}
}

void PepperReloadEntity::hide() {
	this->setEnabled(false);
	this->timeTillSpawn = rand() % 30 + 30;
}
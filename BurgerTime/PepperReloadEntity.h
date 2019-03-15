#pragma once
#include "Entity.h"
#include "Sprite.h"
#include "RenderComponent.h"

class PepperReloadEntity : 	public Entity {
	Sprite* iceCream;
	Sprite* fries;
	RenderComponent* render;
	
	std::vector<Entity*>* stairs;
	double timeTillSpawn;

public:
	PepperReloadEntity(Engine* engine, Entity* player, std::vector<Entity*>* stairs);

	virtual void update(double dt);

private:
	void show();
	void hide();
};


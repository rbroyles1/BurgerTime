#pragma once
#include "Engine.h"
#include "Entity.h"

class Component {
protected:
	Engine* engine;
	Entity* entity;

public:
	Component(Engine* engine, Entity* entity) {
		this->engine = engine;
		this->entity = entity;
	}

	virtual void init() { }
	virtual void update(float dt) { }
	virtual void receive(Message message) { }
	
	virtual ~Component() { }
};
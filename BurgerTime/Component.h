#pragma once
#include "Entity.h"

class Engine;
class Entity;

class Component : public Receiver {
protected:
	Engine* engine;
	Entity* entity;

public:
	Component(Engine* engine, Entity* entity);

	virtual void init();
	virtual void update(double dt);

	virtual ~Component();
};
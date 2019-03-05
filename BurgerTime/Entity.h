#pragma once
#include <vector>
#include "Coordinate.h"
#include "Receiver.h"
#include "Component.h"

class Component;
class Engine;

class Entity : public Receiver {
private:
	std::vector<Component*>* components;

protected:
	unsigned int id;
	Coordinate* position;
	Engine* engine;

public:

	Entity(Engine* engine, Coordinate position);
	Entity(Engine* engine);

	virtual void init();
	virtual void update(double dt);
	virtual void addComponent(Component* component);
	virtual void receive(Message message);

	Coordinate* getPosition();
	void setPosition(Coordinate& position);

	virtual ~Entity();
};
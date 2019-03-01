#pragma once
#include <vector>
#include "Receiver.h"
#include "Component.h"
#include "Coordinate.h"

class Component;

class Entity : public Receiver {
private:
	std::vector<Component*>* components;
	std::vector<Receiver*>* receivers;

protected:
	unsigned int id;
	Coordinate* position;

public:

	Entity(Coordinate position);
	Entity();

	virtual void init();
	virtual void update(double dt);
	virtual void addComponent(Component* component);
	virtual void addReceiver(Receiver* receiver);
	virtual void send(Message message);
	virtual void receive(Message message);

	Coordinate* getPosition();
	void setPosition(Coordinate& position);

	virtual ~Entity();
};
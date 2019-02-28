#pragma once
#include <vector>
#include "Component.h"
#include "Coordinate.h"

enum Message { HIT };
class Component;

class Entity {

protected:
	unsigned int id;
	Coordinate* position;

	std::vector<Component*>* components;
	std::vector<Entity*>* receivers;

public:

	Entity(Coordinate position);
	Entity();

	virtual void init();
	virtual void update(float dt);
	virtual void addComponent(Component* component);
	virtual void addReceiver(Entity *entity);
	virtual void send(Message message);
	virtual void receive(Message message);

	Coordinate* getPosition();
	void setPosition(Coordinate& position);

	virtual ~Entity();
};
#pragma once
#include <vector>
#include "Coordinate.h"
#include "Receiver.h"
#include "Component.h"
#include "BoundingBox.h"

enum CharacterAction { WALK_LEFT, WALK_RIGHT, GO_UPSTAIRS, GO_DOWNSTAIRS, STUNNED, DIE, CELEBRATE_VICTORY, NO_ACTION};

class Component;
class Engine;

class Entity : public Receiver {
private:
	bool enabled;

protected:
	Engine* engine;
	Coordinate* position;
	BoundingBox* boundingBox;
	std::vector<Component*>* components;

public:

	Entity(Engine* engine, Coordinate* position);
	Entity(Engine* engine);

	virtual void init();
	virtual void update(double dt);
	virtual void addComponent(Component* component);

	Component* getComponent(int index);

	Coordinate* getPosition();
	virtual void setPosition(Coordinate& position);

	BoundingBox* getBoundingBox();
	void setBoundingBox(BoundingBox* boundingBox);

	bool getEnabled();
	void setEnabled(bool enabled);

	virtual ~Entity();
};
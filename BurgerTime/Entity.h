#pragma once
#include <vector>
#include <unordered_set>
#include "Coordinate.h"
#include "Receiver.h"
#include "Component.h"
#include "BoundingBox.h"

enum CharacterAction { WALK_LEFT, WALK_RIGHT, GO_UPSTAIRS, GO_DOWNSTAIRS, STUNNED, DIE, CELEBRATE_VICTORY, NO_ACTION};

class Component;
class Engine;

class Entity : public Receiver {
private:
	std::vector<Component*>* components;
	std::unordered_set<Message>* receivedMessages;
	bool enabled;

protected:
	Engine* engine;
	Coordinate* position;
	BoundingBox* boundingBox;

public:

	Entity(Engine* engine, Coordinate* position);
	Entity(Engine* engine);

	virtual void init();
	virtual void update(double dt);
	virtual void addComponent(Component* component);
	virtual void receive(Message message);

	Component* getComponent(int index);

	bool hasReceived(Message message);
	void clearMessages();

	Coordinate* getPosition();
	virtual void setPosition(Coordinate& position);

	BoundingBox* getBoundingBox();
	void setBoundingBox(BoundingBox* boundingBox);

	bool getEnabled();
	void setEnabled(bool enabled);

	virtual ~Entity();
};
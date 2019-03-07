#pragma once
#include <vector>
#include "BoxCollideComponent.h"
#include "Entity.h"

class Engine;
class Entity;
class BoxCollideComponent;

enum Field {FLOOR, STAIR, NO_FIELD};

class Game : public Entity {
	std::vector<Entity*>* entities;
	std::vector<Entity*>* floors;
	std::vector<Entity*>* leftFloorsLimits;
	std::vector<Entity*>* rightFloorsLimits;
	std::vector<Entity*>* stairs;
	std::vector<Entity*>* upStairsLimits;
	std::vector<Entity*>* downStairsLimits;

	Field previousField;
	Coordinate* previousFieldPosition;

public:

	Game(Engine* engine);

	virtual void init();
	virtual void update(double dt);
	virtual void receive(Message message);
	void addEntity(Entity* entity);

	void createFloor(Coordinate* position, int type);
	void createStair(Coordinate* position);
	void createPlayer(Coordinate* position);
	
	virtual ~Game();

private:
	void createGameComponents();
	void createFpsCounter();
	void createLevel();

	void updateLimits(Field newField, Coordinate* position);
	void addStartingLimit(Field newField, Coordinate* position);
	void addEndingLimit();

	void createFloorLimit(Coordinate* position, int type);
	void createStairLimit(Coordinate* position, int type);
};
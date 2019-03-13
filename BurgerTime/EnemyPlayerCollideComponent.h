#pragma once
#include "Component.h"

class EnemyPlayerCollideComponent : public Component {
	std::vector<Entity*>* enemies;

public:
	EnemyPlayerCollideComponent(Engine* engine, Entity* entity, std::vector<Entity*>* enemies);

	virtual void update(double dt);
};


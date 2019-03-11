#pragma once
#include "RigidBodyComponent.h"

class WalkingRigidBodyComponent : public RigidBodyComponent {
	bool isPlayer;

public:
	WalkingRigidBodyComponent(Engine* engine, Entity* entity, bool isPlayer);

	virtual void update(double dt);
};


#pragma once
#include "RigidBodyComponent.h"

class PlayerRigidBodyComponent : public RigidBodyComponent {
public:
	PlayerRigidBodyComponent(Engine* engine, Entity* entity);

	virtual void receive(Message message);
	virtual void update(double dt);
};


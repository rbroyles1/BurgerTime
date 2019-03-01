#pragma once
#include "Component.h"

class RigidBodyComponent : public Component {
protected:
	Coordinate* velocity;

public:
	RigidBodyComponent(Engine* engine, Entity* entity);
	
	virtual void update(double dt);

	~RigidBodyComponent();
};


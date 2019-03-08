#pragma once
#include "RigidBodyComponent.h"
class IngredientRigidBodyComponent : public RigidBodyComponent {

public:
	IngredientRigidBodyComponent(Engine* engine, Entity* entity);

	virtual void update(double dt);
};


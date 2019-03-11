#pragma once
#include "RenderComponent.h"
#include "EnemyEntity.h"
#include "Sprite.h"

class EnemyRenderComponent : public Component {
	Sprite* walkingLeft;
	Sprite* walkingRight;
	Sprite* upStairs;
	Sprite* downStairs;
	Sprite* squashed;
	Sprite* stunned;

	int deadMillisecs;
	int stunnedMillisecs;

public:
	EnemyRenderComponent(Engine* engine, Entity* entity, EnemyType enemyType);

	virtual void update(double dt);

	~EnemyRenderComponent();

private:
	void writeSpritePattern(char* buffer, const char* prePattern, EnemyType enemyType);
};


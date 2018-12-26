#include "InkMonster.h"
#include <stdlib.h>

extern LazyWorld gameWorld;

#define HORIZONTAL_SPEED 0.2

typedef enum
{
	IDLE,
	MOVING,
	SHOOTING,
	ALL_FRAMES,
	FALLING
}inkMonsterState;

InkMonster::InkMonster()
{
	inkMonsterSprite.addSpriteSheet({ "ninja-spritemap.png", 42, 26, 0, 35, 0, 0 });

	inkMonsterSprite.addState({ IDLE, 4, 3, 0, 0 });
	inkMonsterSprite.addState({ MOVING, 3, 4, 0, 1 });
	inkMonsterSprite.addState({ SHOOTING, 4, 4, 0, 4 });

	inkMonsterSprite.setState(IDLE);

	startPos.x = 60;	// Start in a different location than the hero
}

void InkMonster::ai()
{

	b2Vec2 vectorToHero = this->getVectorToEntity(gameWorld.getHero());

	if (vectorToHero.Length() < 20)
	{
		if (vectorToHero.x > 0)
		{
			entityBody->SetLinearVelocity(b2Vec2(HORIZONTAL_SPEED, 1));
		}
		else
		{
			entityBody->SetLinearVelocity(b2Vec2(-HORIZONTAL_SPEED, 1));
		}
	}
	else
	{
		entityBody->SetLinearVelocity(b2Vec2(0, 1));
	}

	updateHealth();
}

void InkMonster::draw()
{
	inkMonsterSprite.draw();
}

InkMonster::~InkMonster()
{

}
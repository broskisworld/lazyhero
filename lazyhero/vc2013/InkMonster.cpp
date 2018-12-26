#include "InkMonster.h"
#include <stdlib.h>

extern LazyWorld gameWorld;

#define HORIZONTAL_SPEED 0.2

InkMonster::InkMonster()
{
	entSpriteSheet = { "ninja-spritemap.png", 35, 0, 0, 0 };

	idle = { 42, 26, 4, 3, 0, 0 };
	running = { 42, 26, 3, 4, 0, 1 };
	attack = { 42, 26, 4, 4, 0, 4 };
	die = { 42, 26, 4, 2, 0, 3 };

	currentAnimation = idle;
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
}

InkMonster::~InkMonster()
{

}
#include "InkMonster.h"
#include "InkBullet.h"
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
}

void InkMonster::ai()
{

	b2Vec2 vectorToHero = this->getVectorToEntity(gameWorld.getHero());

	if (vectorToHero.Length() < 20)
	{
		//fire at hero
		//update time since last shot
		timeSinceLastShot += gameWorld.getDeltaPhysics();

		Entity * newGlob = new InkBullet((vectorToHero.x > 0) ? 1.0 : -1.0);	//move in direction of hero
		newGlob->startPos = entityBody->GetPosition();

		//move towards hero
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
		timeSinceLastShot = 0.0;	//reset firing
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
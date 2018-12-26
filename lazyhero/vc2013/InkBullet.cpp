#include <iostream>
#include <math.h>

using namespace std;

#include "InputManager.h"
#include "LazyWorld.h"
#include "Entity.h"
#include "Animation.h"
#include "InkBullet.h"

extern LazyWorld gameWorld;

using namespace ci;
using namespace ci::app;

typedef enum
{
	FLYING,
	EXPLODING
}bulletState;

InkBullet::InkBullet(double dirFactor)
{
	inkBulletSprite.addSpriteSheet({ "Bullet Splash.png", 11, 18, 0, 0, 0, 0 });

	inkBulletSprite.addState({ FLYING, 4, 3, true, 0, 0 });
	inkBulletSprite.addState({ EXPLODING, 7, 5, false, 0, 1 });

	inkBulletSprite.setState(FLYING);

	entityBody->SetLinearVelocity(b2Vec2(dirFactor * BULLET_FLYING_VELOCITY, 0.0));	//fly in specified direction
}

void InkBullet::draw()
{
	inkBulletSprite.draw();
}

void InkBullet::ai()
{
	if (1)	//TOUCHING
	{
		//stop moving
		entityBody->SetLinearVelocity(b2Vec2(0.0, 0.0));
		
		//show exploding animation
		inkBulletSprite.setState(EXPLODING);

		if (inkBulletSprite.isFinished())
			;//kill entity

		if (!NULL)	//isEntity
			if (1)	//isHero
				;//damage hero
			else if(1)	//isInkMonster
				;//kill entity
	}
	else
	{
		//still flying
	}
}

InkBullet::~InkBullet()
{
	
}
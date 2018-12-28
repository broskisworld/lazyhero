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

InkBullet::InkBullet()
{
	dirFactor = 0.0;
}

InkBullet::InkBullet(double _dirFactor)
{
	inkBulletSprite.addSpriteSheet({ "Bullet Splash.png", 15, 18, 0, 0, 0, 0 });

	inkBulletSprite.addState({ FLYING, 4, 3, true, 0, 0 });
	inkBulletSprite.addState({ EXPLODING, 7, 5, false, 0, 1 });

	inkBulletSprite.setState(FLYING);

	dirFactor = _dirFactor;

	if (dirFactor < 0.0)
		inkBulletSprite.mirror = true;	//if flying left, mirror bullet sprite
}

void InkBullet::draw()
{
	inkBulletSprite.draw();
}

void InkBullet::ai()
{
	if (contacting)	//TOUCHING
	{
		//stop moving
		entityBody->SetLinearVelocity(b2Vec2(0.0, 0.0));
		
		//show exploding animation
		inkBulletSprite.setState(EXPLODING);

		if (inkBulletSprite.isFinished())
			gameWorld.removeEntity(this);
	}
	else
	{     
		//still flying
		b2Vec2 bulletVector = b2Vec2(dirFactor * BULLET_FLYING_VELOCITY, 0.0);
		Entity::entityBody->SetLinearVelocity(bulletVector);	//fly in specified direction
	}
}

/*void startContact(Entity *contactingEntity)
{


	Entity::startContact();
}

void endContact(Entity *contactingEntity)
{
	Entity::endContact();
}*/

InkBullet::~InkBullet()
{
	
}
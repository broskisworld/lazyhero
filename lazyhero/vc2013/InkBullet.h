#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Animation.h"

extern LazyWorld gameWorld;

#define BULLET_FLYING_VELOCITY 1.0

class InkBullet : public Entity
{
	Animation inkBulletSprite;

	double dirFactor;
public:
	InkBullet();
	InkBullet(double dirFactor);	//1.0 for going right, -1.0 for left

	void draw() override;
	void ai() override;

	void startContact(Entity *contactingEntity) override
	{
		if (contactingEntity != NULL)
		{
			if (contactingEntity == gameWorld.getHero())
				;	//deal damage
		}

		Entity::startContact(contactingEntity);
	}

	~InkBullet();
};
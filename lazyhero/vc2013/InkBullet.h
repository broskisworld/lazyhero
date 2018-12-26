#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Animation.h"

#define BULLET_FLYING_VELOCITY 2.0

class InkBullet : public Entity
{
	Animation inkBulletSprite;
public:
	InkBullet(double dirFactor);	//1.0 for going right, -1.0 for left

	void draw() override;
	void ai() override;

	~InkBullet();
};
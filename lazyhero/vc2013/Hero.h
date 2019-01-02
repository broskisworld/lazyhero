#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Animation.h"

#define HERO_HEALTH 100.0f
#define HERO_WALKING_VELOCITY 0.7f
#define HERO_JUMPING_FORCE 15.0f

class Hero : public Entity
{
	//animation
	Animation heroSprite;

	//movement
	bool touching;
	bool touchingLeft;
	bool touchingRight;
	int leftJumpStat;
	int rightJumpStat;
	int jumpingStat;
public:
	Hero();
	
	void draw() override;
	void ai() override;

	~Hero();
};
#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Hero.h"

#define HERO_BOREDOM_THRESHOLD 8.0	//seconds? roughly
#define HERO_TIRED_THRESHOLD 12.0

#define HERO_WALKING_VELOCITY 2.0
#define HERO_JUMPING_FORCE 15.0

typedef enum
{
	IDLE,
	WANDER,
	FOLLOWING
}heroState;

class Hero : Entity
{
	heroState curState;
	double boredomFactor;
	double tiredFactor;
public:
	Hero();
	
	void ai();
	heroState getCurState();

	~Hero();
};
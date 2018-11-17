#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Hero.h"

#define HERO_BOREDOM_THRESHOLD 8.0	//seconds? roughly
#define HERO_TIRED_THRESHOLD 12.0

#define HERO_WALKING_VELOCITY 0.9
#define HERO_JUMPING_FORCE 15.0

typedef enum
{
	IDLE,
	WANDER,
	FOLLOWING
}heroState;

class Hero : public Entity
{
public:
	heroState curState;
	double boredomFactor;
	double tiredFactor;
	bool touching;
	int jumpingStat;

	//animations
	animation idle;
	animation crouch;
	animation run;
	animation jump;
	animation slide;
	animation ledgeClimb;
	animation allFrames;
	animation falling;

	Hero();
	
	void ai() override;
	heroState getCurState();

	~Hero();
};
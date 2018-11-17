#include <iostream>
#include <math.h>

using namespace std;

#include "GodController.h"
#include "LazyWorld.h"
#include "Entity.h"
#include "Hero.h"

Hero::Hero()
{
	curState = IDLE;
}

void Hero::ai()
{
	//state control
	if (1/*GodController.hasRevelation()*/)
		curState = FOLLOWING;

	//increment boredom
	boredomFactor += 0.001;

	//handle based off state
	switch (curState)
	{
	case IDLE:
		if (boredomFactor > HERO_BOREDOM_THRESHOLD)
			;	//START WANDERING

		//stay still af

		break;
	case WANDER:
		if (tiredFactor > HERO_TIRED_THRESHOLD)
			curState = IDLE;

		//keep walking towards desiredX
		break;
	case FOLLOWING:
		revelation curRevelation = GO_RIGHT/*GodController.hasRevelation()*/;
		
		switch (curState)
		{
		case GO_LEFT:
			boredomFactor = 0.0;	//reset boredom
			
			if (/*touching ground*/1)
				if (/*Entity::entityBody->GetLinearVelocity().x > -(HERO_WALKING_VELOCITY)*/1)	//wait to slow down?
					Entity::entityBody->SetLinearVelocity(b2Vec2(-HERO_WALKING_VELOCITY, Entity::entityBody->GetLinearVelocity().y));

			break;
		case GO_RIGHT:
			boredomFactor = 0.0;	//reset boredom

			if (1)	//touching ground
				Entity::entityBody->SetLinearVelocity(b2Vec2(HERO_WALKING_VELOCITY, Entity::entityBody->GetLinearVelocity().y));
			break;
		case JUMP:
			boredomFactor = 0.0;	//reset boredom

			if (1)	//touching ground
				Entity::entityBody->ApplyForceToCenter(b2Vec2(0.0, HERO_JUMPING_FORCE));
			break;
		case NO_REVELATION:
			//increment boredom
			break;

			if (boredomFactor > HERO_BOREDOM_THRESHOLD)
				curState = IDLE;
		}
		break;
	}
}

//utility
heroState Hero::getCurState() { return curState; }

Hero::~Hero()
{

}
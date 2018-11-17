#include <iostream>
#include <math.h>

using namespace std;

#include "GodController.h"
#include "LazyWorld.h"
#include "Entity.h"
#include "Hero.h"

extern LazyWorld gameWorld;
extern GodController godInput;

using namespace ci;
using namespace ci::app;

Hero::Hero()
{
	curState = IDLE;

	entSpriteSheet = { "adventurer-v1.5-Sheet.png", 35, 0, 0, 0 };

	idle = { 50,37,4,5,0,0 };
	crouch = { 50,37,4,10,4,0 };
	run = { 50,37,6,10,1,1 };
	jump = { 50,37,10,20,0,2 };
	slide = { 50,37,5,10,3,3 };
	ledgeClimb = { 50,37,9,10,1,4 };
	allFrames = { 50,37,50,10,1,1 };
	falling = { 50,37,2,10,1,3 };
	jumpingStat = 0;
	leftJumpStat = 0;
	rightJumpStat = 0;
}

void Hero::ai()
{
	//STATE-INDEPENDANT
	//state control
	if (1/*GodController.hasRevelation()*/)
		curState = FOLLOWING;

	//increment boredom
	//boredomFactor += 0.001;

	//talk to camera
	//console() << "HERO XY\t" << entityBody->GetPosition().x << ", " << entityBody->GetPosition().y << endl;
	//vec2 v = gameWorld.cam.camToWorldPos(vec2(Entity::entityBody->GetPosition().x, Entity::entityBody->GetPosition().y));
	vec2 v = vec2(Entity::entityBody->GetPosition().x * gameWorld.cam.scale, Entity::entityBody->GetPosition().y * gameWorld.cam.scale);
	//console() << v.x << endl;
	//console() << "Actual Cam" << gameWorld.cam.pos << endl;
	gameWorld.cam.setFixPoint(v.x,v.y);
	v = vec2(Entity::entityBody->GetPosition().x, Entity::entityBody->GetPosition().y);
	b2Vec2 j = gameWorld.raycast(b2Vec2(v.x, v.y), b2Vec2(v.x, v.y + 1.2));
	b2Vec2 j2 = gameWorld.raycast(b2Vec2(v.x - 0.45, v.y), b2Vec2(v.x - 0.45, v.y + 1.2));
	b2Vec2 j3 = gameWorld.raycast(b2Vec2(v.x + 0.45, v.y), b2Vec2(v.x + 0.45, v.y + 1.2));
	b2Vec2 jv = b2Vec2(j.x - v.x, j.y - v.y);
	b2Vec2 jv2 = b2Vec2(j2.x - (v.x - 0.45), j2.y - v.y);
	b2Vec2 jv3 = b2Vec2(j3.x - (v.x + 0.45), j3.y - v.y);
	if (jv.Length() < 1.1 || jv2.Length() < 1.1 || jv3.Length() < 1.1) {
		touching = true;
		if (jumpingStat != 0) {
			jumpingStat = jumpingStat + 1;
			if (jumpingStat > 10) {
				jumpingStat = 0;
			}
		}
	}
	else {
		touching = false;
		
	}
	v = vec2(Entity::entityBody->GetPosition().x, Entity::entityBody->GetPosition().y);
	j = gameWorld.raycast(b2Vec2(v.x, v.y), b2Vec2(v.x + 0.7, v.y));
	j3 = gameWorld.raycast(b2Vec2(v.x, v.y- 0.95), b2Vec2(v.x + 0.7, v.y - 0.95));
	
	
	jv = b2Vec2(j.x - v.x, j.y - v.y);
	jv3 = b2Vec2(j3.x - v.x, j3.y -( v.y - 0.95));
	if (jv.Length() < 0.6 || jv3.Length() < 0.6) {
		touchingRight = true;
		if (rightJumpStat != 0) {
			rightJumpStat = rightJumpStat + 1;
			if (rightJumpStat > 10) {
				rightJumpStat = 0;
			}
		}
	}
	else {
		touchingRight = false;

	}
	v = vec2(Entity::entityBody->GetPosition().x, Entity::entityBody->GetPosition().y);
	j = gameWorld.raycast(b2Vec2(v.x, v.y), b2Vec2(v.x - 0.7, v.y));
	j3 = gameWorld.raycast(b2Vec2(v.x, v.y - 0.95), b2Vec2(v.x - 0.7, v.y - 0.95));
	jv = b2Vec2(j.x - v.x, j.y - v.y);
	jv3 = b2Vec2(j3.x - v.x, j3.y - (v.y - 0.95));
	if (jv.Length() < 0.6 || jv3.Length() < 0.6) {
		touchingLeft = true;
		if (leftJumpStat != 0) {
			leftJumpStat = leftJumpStat + 1;
			if (leftJumpStat > 10) {
				leftJumpStat = 0;
			}
		}
	}
	else {
		touchingLeft = false;

	}

	
	//console() << "x " << j.x << " y " << j.y << " length " << jv.Length() << endl;
	//gl::drawLine()
	//STATE-DEPENDANT
	//handle based off state
	if (Entity::entityBody->GetLinearVelocity().x > 0) {
		flip = false;
	}
	else if(Entity::entityBody->GetLinearVelocity().x < 0){
		flip = true;
	}
	if (godInput.w) {
		if (touching && jumpingStat == 0) {	//touching ground
			currentAnimation = jump;
			currentFrame = 0;
			jumpingStat = 1;
			Entity::entityBody->ApplyForceToCenter(b2Vec2(0.0, -HERO_JUMPING_FORCE));
			touching = false;
		}
		if (touchingLeft && leftJumpStat == 0) {
			currentAnimation = jump;
			currentFrame = 0;
			leftJumpStat = 1;
			Entity::entityBody->SetLinearVelocity(b2Vec2(0.9, -0.8));
			flip = true;
			touchingLeft = false;
		}
		if (touchingRight && rightJumpStat == 0) {
			currentAnimation = jump;
			currentFrame = 0;
			rightJumpStat = 1;
			Entity::entityBody->SetLinearVelocity(b2Vec2(-0.9, -0.8));
			flip = true;
			touchingRight = false;
		}
		if (touching == false && currentFrame == jump.numFrames - 2) {
			currentAnimation = falling;
			//currentFrame = 0;
		}
	}

	if (godInput.d) {
		if (touching) {
			currentAnimation = run;

			boredomFactor = 0.0;	//reset boredom


		}
		
		if (Entity::entityBody->GetLinearVelocity().x < HERO_WALKING_VELOCITY) {
			if (touching) {
				Entity::entityBody->SetLinearVelocity(b2Vec2(0.1 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
			}
			else
			{
				if (!touchingRight) {
					Entity::entityBody->SetLinearVelocity(b2Vec2(0.03 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));

				}
			}
		}
		if (touching == false && currentFrame == jump.numFrames - 2) {
			currentAnimation = falling;
			//currentFrame = 0;
		}
	}
	if (godInput.a) {
		if (touching) {
			currentAnimation = run;

			boredomFactor = 0.0;//reset boredom
		}
		if (/*Entity::entityBody->GetLinearVelocity().x > -(HERO_WALKING_VELOCITY)*/1 == 1)	//wait to slow down?
			if (Entity::entityBody->GetLinearVelocity().x > -HERO_WALKING_VELOCITY) {
				if (touching) 
				{
					Entity::entityBody->SetLinearVelocity(b2Vec2(-0.1 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
				}
				else
				{
					if (!touchingLeft) {
						Entity::entityBody->SetLinearVelocity(b2Vec2(-0.03 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));

					}
					else {
						Entity::entityBody->SetLinearVelocity(b2Vec2(0, Entity::entityBody->GetLinearVelocity().y));
					}
				}
			}

		if (touching == false && currentFrame == jump.numFrames - 2) {
			currentAnimation = falling;
			//currentFrame = 0;
		}
	}
	if (!godInput.w && !godInput.a && !godInput.d) {
		if (touching && jumpingStat != 0) {
			currentAnimation = crouch;
		}
		if (touching) {
			Entity::entityBody->SetLinearVelocity(b2Vec2(Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y+0.4f));
		}
		if (touching && jumpingStat == 0) {
			currentAnimation = idle;
		}
		if (touching == false && currentFrame == jump.numFrames - 2) {
			currentAnimation = falling;
			//currentFrame = 0;
		}
	}
	switch (curState)
	{
	case IDLE:
		if (boredomFactor > HERO_BOREDOM_THRESHOLD)
			;	//START WANDERING

		//stay still af
		currentAnimation = idle;
		break;
	case WANDER:
		if (tiredFactor > HERO_TIRED_THRESHOLD)
			curState = IDLE;
		
		

		//keep walking towards desiredX

		currentAnimation = jump;
		break;
	case FOLLOWING:
		b2Vec2 newVec(b2Vec2(HERO_WALKING_VELOCITY, Entity::entityBody->GetLinearVelocity().y));
		revelation curRevelation = godInput.getRevelation();
		//console() << curRevelation << endl;
		switch (curRevelation)
		{
		case GO_LEFT:
			
					
			

			break;
		case GO_RIGHT:
			
			break;
		case JUMP:
			boredomFactor = 0.0;	//reset boredom

			
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
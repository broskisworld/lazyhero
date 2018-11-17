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
	b2Vec2 jv = b2Vec2(j.x - v.x, j.y - v.y);
	if (jv.Length() < 1.1) {
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

	
	console() << "x " << j.x << " y " << j.y << " length " << jv.Length() << endl;
	//gl::drawLine()
	//STATE-DEPENDANT
	//handle based off state
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
			if (touching) {
				currentAnimation = run;

				boredomFactor = 0.0;//reset boredom
			}
			if (Entity::entityBody->GetLinearVelocity().x < 0) {
				flip = true;
			}
				if (/*Entity::entityBody->GetLinearVelocity().x > -(HERO_WALKING_VELOCITY)*/1 == 1)	//wait to slow down?
					if (Entity::entityBody->GetLinearVelocity().x > -HERO_WALKING_VELOCITY) {
						Entity::entityBody->SetLinearVelocity(b2Vec2(-0.1 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
					}

			if (touching == false && currentFrame == jump.numFrames - 2) {
				currentAnimation = falling;
					//currentFrame = 0;
			}
					
			

			break;
		case GO_RIGHT:
			if (touching) {
				currentAnimation = run;
				
				boredomFactor = 0.0;	//reset boredom

				
			}
			if (Entity::entityBody->GetLinearVelocity().x > 0) {
				flip = false;
			}
			if (Entity::entityBody->GetLinearVelocity().x < HERO_WALKING_VELOCITY) {
				Entity::entityBody->SetLinearVelocity(b2Vec2(0.1 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
			}
			if (touching == false && currentFrame == jump.numFrames - 2) {
				currentAnimation = falling;
				//currentFrame = 0;
			}
			break;
		case JUMP:
			boredomFactor = 0.0;	//reset boredom

			if (touching && jumpingStat == 0) {	//touching ground
				currentAnimation = jump;
				currentFrame = 0;
				jumpingStat = 1;
				Entity::entityBody->ApplyForceToCenter(b2Vec2(0.0, -HERO_JUMPING_FORCE));
			}
			if (touching == false && currentFrame == jump.numFrames-2) {
				currentAnimation = falling;
				//currentFrame = 0;
			}
			break;
		case NO_REVELATION:
			if (touching && jumpingStat != 0) {
				currentAnimation = crouch;
			}
			if (touching && jumpingStat == 0 ) {
				currentAnimation = idle;
			}
			if (touching == false && currentFrame == jump.numFrames - 2) {
				currentAnimation = falling;
				//currentFrame = 0;
			}
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
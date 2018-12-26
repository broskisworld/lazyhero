#include <iostream>
#include <math.h>

using namespace std;

#include "InputManager.h"
#include "LazyWorld.h"
#include "Entity.h"
#include "Animation.h"
#include "Hero.h"

extern LazyWorld gameWorld;
extern InputManager controls;

using namespace ci;
using namespace ci::app;

typedef enum
{
	IDLE,
	CROUCH,
	RUN,
	JUMP,
	SLIDE,
	LEDGE_CLIMB,
	ALL_FRAMES,
	FALLING
}heroState;

Hero::Hero()
{
	heroSprite.addSpriteSheet({ "adventurer-v1.5-Sheet.png", 50, 37, 0, 25, 0, 0 });

	heroSprite.addState({ IDLE, 4, 5, true, 0, 0 });
	heroSprite.addState({ CROUCH, 4, 10, true, 4, 0 });
	heroSprite.addState({ RUN, 6, 10, true, 1, 1 });
	heroSprite.addState({ JUMP, 10, 20, true, 0, 2 });
	heroSprite.addState({ SLIDE, 5, 10, true, 3, 3 });
	heroSprite.addState({ LEDGE_CLIMB, 9, 10, true, 1, 4 });
	heroSprite.addState({ ALL_FRAMES, 50, 10, true, 1, 1 });
	heroSprite.addState({ FALLING, 2, 10, true, 1, 3 });
	
	jumpingStat = 0;
	leftJumpStat = 0;
	rightJumpStat = 0;

	heroSprite.setState(FALLING);
}

void Hero::draw()
{
	heroSprite.draw();
}

void Hero::ai()
{
	//talk to camera
	//console() << "HERO XY\t" << entityBody->GetPosition().x << ", " << entityBody->GetPosition().y << endl;
	//vec2 v = gameWorld.cam.camToWorldPos(vec2(Entity::entityBody->GetPosition().x, Entity::entityBody->GetPosition().y));
	vec2 v = vec2(Entity::entityBody->GetPosition().x * gameWorld.cam.scale, Entity::entityBody->GetPosition().y * gameWorld.cam.scale);
	//console() << v.x << endl;
	//console() << "Actual Cam" << gameWorld.cam.pos << endl;
	gameWorld.cam.setFixPoint(v.x,v.y);
	
	//much of the code below is for wall-jumping mechanics, and I am talking to my buddy TJ to understand a bit more of what's going on here because tbh a lot of this i don't know what he's trying to do

	//check what objects you're touching
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

	//handle controls
	
	if (Entity::entityBody->GetLinearVelocity().x > 0) {
		heroSprite.mirror = false;
	}
	else if(Entity::entityBody->GetLinearVelocity().x < 0){
		heroSprite.mirror = true;
	}
	if (controls.w) {
		if (touching && jumpingStat == 0) {	//touching ground
			heroSprite.setState(JUMP);
			jumpingStat = 1;
			Entity::entityBody->ApplyForceToCenter(b2Vec2(0.0, -HERO_JUMPING_FORCE));
			touching = false;
		}
		if (touchingLeft && leftJumpStat == 0) {
			heroSprite.setState(JUMP);
			leftJumpStat = 1;
			Entity::entityBody->SetLinearVelocity(b2Vec2(0.9, -0.8));
			heroSprite.mirror = true;
			touchingLeft = false;
		}
		if (touchingRight && rightJumpStat == 0) {
			heroSprite.setState(JUMP);
			rightJumpStat = 1;
			Entity::entityBody->SetLinearVelocity(b2Vec2(-0.9, -0.8));
			heroSprite.mirror = true;
			touchingRight = false;
		}
		//if (touching == false && currentFrame == jump.numFrames - 2) {	//TJ: is this okay?
		if(touching == false)
		{
			heroSprite.setState(FALLING);
			//currentFrame = 0;
		}
	}

	if (controls.d)
	{
		if (touching)
		{
			heroSprite.setState(RUN);
		}
		
		if (Entity::entityBody->GetLinearVelocity().x < HERO_WALKING_VELOCITY)
		{
			if (touching)
			{
				Entity::entityBody->SetLinearVelocity(b2Vec2(0.1 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
			}
			else
			{
				if (!touchingRight)
				{
					Entity::entityBody->SetLinearVelocity(b2Vec2(0.03 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
				}
			}
		}
		//if (touching == false && currentFrame == jump.numFrames - 2) {
		if(touching == false)	//TJ: is this okay?
		{
			heroSprite.setState(FALLING);
		}
	}
	if (controls.a)
	{
		if (touching)
		{
			heroSprite.setState(RUN);
		}
		if (/*Entity::entityBody->GetLinearVelocity().x > -(HERO_WALKING_VELOCITY)*/1 == 1)	//wait to slow down?
			if (Entity::entityBody->GetLinearVelocity().x > -HERO_WALKING_VELOCITY) {
				if (touching) 
				{
					Entity::entityBody->SetLinearVelocity(b2Vec2(-0.1 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));
				}
				else
				{
					if (!touchingLeft)
					{
						Entity::entityBody->SetLinearVelocity(b2Vec2(-0.03 + Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y));

					}
					else
					{
						Entity::entityBody->SetLinearVelocity(b2Vec2(0, Entity::entityBody->GetLinearVelocity().y));
					}
				}
			}

		if (touching == false/* && currentFrame == jump.numFrames - 2*/)	//TJ: same
		{
			heroSprite.setState(FALLING);
		}
	}
	if (!controls.w && !controls.a && !controls.d) {
		if (touching && jumpingStat != 0)
		{
			heroSprite.setState(CROUCH);
		}
		if (touching)
		{
			Entity::entityBody->SetLinearVelocity(b2Vec2(Entity::entityBody->GetLinearVelocity().x, Entity::entityBody->GetLinearVelocity().y+0.4f));
		}
		if (touching && jumpingStat == 0)
		{
			heroSprite.setState(IDLE);
		}
		if (touching == false/* && currentFrame == jump.numFrames - 2*/)	//TJ: ditto. idk what this code is for - is it a special animation feature?
		{
			heroSprite.setState(FALLING);
		}
	}
	updateHealth();
}

Hero::~Hero()
{

}
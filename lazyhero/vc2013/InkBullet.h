#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Animation.h"

extern LazyWorld gameWorld;

#define BULLET_FLYING_VELOCITY 1.0f
#define BULLET_DAMAGE 10.0f

class InkBullet : public Entity
{
	Animation inkBulletSprite;

	double dirFactor;
	bool triggerExplosion;
	//b2WeldJointDef explodingJointDef;
	//b2WeldJoint * explodingJoint;

public:
	InkBullet();
	InkBullet(double dirFactor);	//1.0 for going right, -1.0 for left

	void draw() override;
	void ai() override;

	void startContact(b2Fixture * contactingFixture, Entity *contactingEntity) override
	{
		//if (contactingEntity != NULL && (contactingEntity->collideWithWhat & entityColliderType))
			//return;

		if (!contacting)
		{
			if (contactingEntity == gameWorld.getHero())
				contactingEntity->changeHealth(-BULLET_DAMAGE);
			else
			{
				//define joint for use on next ai() call
				/*explodingJointDef.bodyA = this->entityBody;
				explodingJointDef.bodyB = contactingFixture->GetBody();
				explodingJointDef.localAnchorA = b2Vec2(-0.5f, -0.5f);
				explodingJointDef.localAnchorB = b2Vec2(0.5f, 0.5f);
				explodingJointDef.collideConnected = true;*/

				triggerExplosion = true;
			}
		}

		Entity::startContact(contactingFixture, contactingEntity);
	}

	~InkBullet();
};
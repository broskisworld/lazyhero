#pragma once

#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <Box2D/Box2D.h>

using namespace std;
using namespace ci;
using namespace ci::app;

#include "LazyWorld.h"

class Entity
{
protected:
	float health;
	bool contacting;

public:
	//int currentFrame;
	//double timeSinceLastFrame;
	//gl::Texture2dRef mTexture;
	//spriteSheet entSpriteSheet;
	//animation currentAnimation;
	b2Vec2 startPos;
	b2Body* entityBody;
	//bool flip;
	//Texture2d curTexture;

	Entity();
	void initPhysics();
	virtual void ai();
	virtual void physics();
	virtual void draw();
	b2Vec2 getVectorToEntity(Entity* targetEntity);
	void updateHealth();
	virtual void startContact(Entity *contactingEntity);
	virtual void endContact(Entity *contactingEntity);

	~Entity();
};
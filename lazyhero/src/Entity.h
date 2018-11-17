#pragma once

#include <iostream>

#include <Box2D/Box2D.h>
using namespace std;

#include "LazyWorld.h"

class Entity
{
	b2Vec2 pos;
	b2Body* entityBody;
	//Texture2d curTexture;

public:
	Entity();
	void initPhysics(b2World * physWorld);
	void update();
	void moveRight();
	virtual void ai();
	virtual void physics();
	virtual void draw();
	~Entity();
};
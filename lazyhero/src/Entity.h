#pragma once

#include <iostream>

#include <Box2D/Box2D.h>
using namespace std;

#include "LazyWorld.h"

class Entity
{
public:
	b2Vec2 startPos;
	b2Body* entityBody;
	//Texture2d curTexture;

	Entity();
	void initPhysics();
	virtual void ai();
	virtual void physics();
	virtual void draw();
	~Entity();
};
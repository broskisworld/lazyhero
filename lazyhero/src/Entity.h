#pragma once

#include <iostream>

#include <Box2D/Box2D.h>
using namespace std;

#include "LazyWorld.h"

class Entity
{
protected:
	b2Vec2 pos;
	b2Body* entityBody;
	//Texture2d curTexture;

public:
	Entity();
	void initPhysics(b2World * physWorld);
	void Update();
	void MoveRight();
	virtual void ai();
	virtual void physics();
	virtual void draw();
	~Entity();
};
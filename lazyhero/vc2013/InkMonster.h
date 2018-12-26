#pragma once

#include <iostream>
#include <math.h>

using namespace std;

#include "LazyWorld.h"
#include "InputManager.h"
#include "Entity.h"
#include "Animation.h"

class InkMonster : public Entity
{
private:
	b2Vec2 movement;
	int direction;
	double timeSinceLastShot;

	//animation
	Animation inkMonsterSprite;

public:
	InkMonster();
	void ai();
	void draw() override;
	~InkMonster();
};
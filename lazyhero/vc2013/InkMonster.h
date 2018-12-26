#pragma once

#include <iostream>
#include <math.h>

using namespace std;

#include "LazyWorld.h"
#include "InputManager.h"
#include "Entity.h"

class InkMonster : public Entity
{
private:
	animation idle, running, attack, die;
	b2Vec2 movement;
	int direction;

public:
	InkMonster();
	void ai();
	~InkMonster();
};
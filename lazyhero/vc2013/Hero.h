#pragma once

#include <iostream>

//#include <Box2d.h>

using namespace std;

#include "LazyWorld.h"
#include "Entity.h"
#include "Hero.h"

class Hero : Entity
{
public:
	void ai();
}
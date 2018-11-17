#pragma once

#include <iostream>
#include <Box2D/Box2D.h>

using namespace std;

class Block
{
public:
	int type;
	Block();
	Block(int _type);
};
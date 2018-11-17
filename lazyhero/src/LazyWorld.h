#pragma once

#include <iostream>
#include <vector>
#include "Block.h"
#include "Line.h"
using namespace std;

class LazyWorld
{
	int WORLD_WIDTH_BLOCK = 100;
	int WORLD_HEIGHT_BLOCK = 100;
	double WORLD_SCALE_BLOCK = 5;
	vector<vector<Block>> worldData;
	vector<Line2> blockRigidBodies;
	b2World * physWorld;
public:
	LazyWorld();
	void addPhysics(b2World * _physLazyWorld);
	void buildLevel0();
	Block getBlockAt(int x, int y);
	vector<Line2> createWorldFromList(b2World * mWorld, vector<b2Body*>		mBoxes);
	int getBlockWidth();
	int getBlockHeight();
	double getBlockScale();
	~LazyWorld();
};
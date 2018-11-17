#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>

#include <iostream>
#include <vector>

using namespace std;

#include "Block.h"
#include "Line.h"

class LazyWorld
{
	//static boxes
	int WORLD_WIDTH_BLOCK = 100;
	int WORLD_HEIGHT_BLOCK = 100;
	double WORLD_SCALE_BLOCK = 10;
	vector<vector<Block>> worldData;
	vector<Line2> blockOutlines;

	//entities
	//vector<Entity> worldEntities;

	//overall physics
	b2World * physWorld;
	vector<b2Body*> physicsBodies;

	//camera
	double cameraX, cameraY, cameraScale;
public:
	//constructor
	LazyWorld();

	//init physics/graphics
	void initPhysics();

	//levels
	void buildLevel0();
	vector<Line2> createWorldFromList();

	//physics/entity/test shit
	void createTestBox(double x, double y);

	//update
	void stepPhysics();
	void stepAI();
	void render();

	//utility
	Block getBlockAt(int x, int y);
	int getBlockWidth();
	int getBlockHeight();
	double getBlockScale();

	//destructor
	~LazyWorld();
};
#include <iostream>
#include <vector>
#include <list>
#include <Box2D/Box2D.h>


using namespace std;

#include "LazyWorld.h"
#include "Line.h"
#include "Block.h"


LazyWorld::LazyWorld()
{
	//instantiate vars
	for (int x = 0; x < WORLD_WIDTH_BLOCK; x++)
	{
		Block jim(0);
		vector<Block> bob(WORLD_HEIGHT_BLOCK, jim);
		worldData.push_back(bob);	//Fill 
	}
}

void LazyWorld::buildLevel0()
{
	//one-time level constructor
	//hard coded in blocks and entities

	//Instantiate all blocks to air
	for (int x = 0; x < WORLD_WIDTH_BLOCK; x++)
		for (int y = 0; y < WORLD_HEIGHT_BLOCK; y++)
		{
			Block bob(0);
			worldData[x][y] = bob;
		}
	
	for (int i = 0; i < WORLD_WIDTH_BLOCK; i++) {
		worldData[i][60].type = 1;
	}
	
	worldData[45][10].type = 1;

	worldData[80][10].type = 1;
	worldData[45][34].type = 1;

	//CREATE BLOCKS FOR LEVEL

	//CREATE ENTITIES

	//generate box2d physics objects from list of blocks
	//createWorldFromList();

	//generate box2d physics objects for entities (or have entities self call that)
}

Block LazyWorld::getBlockAt(int x, int y)
{
	return worldData[x][y];
}

void LazyWorld::addPhysics(b2World * _physWorld)
{
	physWorld = _physWorld;
}

vector<Line2> LazyWorld::createWorldFromList(b2World * mWorld, vector<b2Body*>mBoxes) {
	vector<Line2> addLines;
	//Run a for loop for a horizontal adding of lines
	for(int j = 0; j < WORLD_HEIGHT_BLOCK; j++)
	{
		for(int i = 0; i < WORLD_WIDTH_BLOCK; i++)
		{
		//TODO might need to take out this littl epart with the currBlock and just test the block using the getBlock function
			//currBlock = getBlockAt(i, j);
			if (getBlockAt(i,j).type != 0)
			{
				//Test block above if it is air
				if (j + 1 < WORLD_HEIGHT_BLOCK) {
					if (getBlockAt(i, j + 1).type == 0 && (j + 1) < WORLD_HEIGHT_BLOCK)
					{
						//start a loop that will keep going to the right we will later adjust the i index
						bool keepGoing = true;
						int startIndex = i;
						int currIndex = i;
						int endIndex = i;
						while (keepGoing && currIndex < WORLD_WIDTH_BLOCK)
						{

							if (getBlockAt(currIndex, j + 1).type == 0 && getBlockAt(currIndex, j).type != 0)
							{
								endIndex = currIndex;
							}
							else
							{
								keepGoing = false;
							}
							currIndex++;
						}
						if (i >= WORLD_WIDTH_BLOCK)
						{
							endIndex = i - 1;
						}
						//Add the line object from the start index position to the end index position
						//Line object for the top of a block
						Line2 line;
						line.p1.x = (double)(startIndex + -0.5) * WORLD_SCALE_BLOCK;
						line.p1.y = (double)(j + 0.5) * WORLD_SCALE_BLOCK;
						line.p2.x = (double)(endIndex + 0.5) * WORLD_SCALE_BLOCK;
						line.p2.y = (double)(j + 0.5) * WORLD_SCALE_BLOCK;
						addLines.push_back(line);
						//add to line list
						i = endIndex;

					}
				}
				if (j - 1 > 0)
				{
					if (getBlockAt(i, j - 1).type == 0)
					{
						bool keepGoing = true;
						int startIndex = i;
						int currIndex = i;
						int endIndex = i;
						while (keepGoing && currIndex < WORLD_WIDTH_BLOCK)
						{

							if (getBlockAt(currIndex, j - 1).type == 0 && getBlockAt(currIndex,j).type != 0)
							{
								endIndex = currIndex;
							}
							else
							{
								keepGoing = false;
							}
							
							currIndex++;
						}
						if (i >= WORLD_WIDTH_BLOCK)
						{
							endIndex = i - 1;
						}
						//Add the line object from the start index position to the end index position
						//This line object is a bottom of a block
						Line2 line;
						line.p1.x = (double)(startIndex + -0.5) * WORLD_SCALE_BLOCK;
						line.p1.y = (double)(j - 0.5) * WORLD_SCALE_BLOCK;
						line.p2.x = (double)(endIndex + 0.5) * WORLD_SCALE_BLOCK;
						line.p2.y = (double)(j - 0.5) * WORLD_SCALE_BLOCK;
						addLines.push_back(line);
						//add to line list
						i = endIndex;

					}
				}
			}
		}
	}
	//Run a loop vertically for vertical lines
	for (int j = 0; j < WORLD_WIDTH_BLOCK; j++)
	{
		for (int i = 0; i < WORLD_HEIGHT_BLOCK; i++)
		{
			//currBlock = getBlockAt(j, i);

			if (getBlockAt(j,i).type != 0)
			{
				if (j - 1 > 0)
				{
					if (getBlockAt(j - 1, i).type == 0)
					{
						bool keepGoing = true;
						int startIndex = i;
						int currIndex = i;
						int endIndex = i;
						while (keepGoing && currIndex < WORLD_HEIGHT_BLOCK)
						{

							if (getBlockAt(j - 1, currIndex).type == 0 && getBlockAt(j, currIndex).type != 0)
							{
								endIndex = currIndex;
							}
							else
							{
								keepGoing = false;
							}
							
							currIndex++;
						}
						if (i >= WORLD_HEIGHT_BLOCK)
						{
							endIndex = i - 1;
						}
						//Add the line object from the start index position to the end index position
						//This line object is a bottom of a block
						Line2 line;
						line.p1.x = (double)(j + -0.5) * WORLD_SCALE_BLOCK;
						line.p1.y = (double)(startIndex - 0.5) * WORLD_SCALE_BLOCK;
						line.p2.x = (double)(j + -0.5) * WORLD_SCALE_BLOCK;
						line.p2.y = (double)(endIndex + 0.5) * WORLD_SCALE_BLOCK;
						addLines.push_back(line);
						//add to line list
						i = endIndex;
					}
				}
				if (j + 1 < WORLD_WIDTH_BLOCK) {
					if (getBlockAt(j + 1, i).type == 0)
					{
						bool keepGoing = true;
						int startIndex = i;
						int currIndex = i;
						int endIndex = i;
						while (keepGoing && currIndex < WORLD_HEIGHT_BLOCK)
						{

							if (getBlockAt(j - 1, currIndex).type == 0 && getBlockAt(j, currIndex).type != 0)
							{
								endIndex = currIndex;
							}
							else
							{
								keepGoing = false;
							}
							currIndex++;
						}
						if (i >= WORLD_HEIGHT_BLOCK)
						{
							endIndex = i - 1;
						}
						//Add the line object from the start index position to the end index position
						//This line object is a bottom of a block
						Line2 line;
						line.p1.x = (double)(j + 0.5) * WORLD_SCALE_BLOCK;
						line.p1.y = (double)(startIndex - 0.5) * WORLD_SCALE_BLOCK;
						line.p2.x = (double)(j + 0.5) * WORLD_SCALE_BLOCK;
						line.p2.y = (double)(endIndex + 0.5) * WORLD_SCALE_BLOCK;
						addLines.push_back(line);
						//add to line list
						i = endIndex;
					}
				}
			}
		
		}
	}
	
	for (int i = 0; i < addLines.size(); i++) 
	{
		Line2 line = addLines[i];
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		b2Vec2 pos = b2Vec2(0, 0);//b2Vec2((line.p1.x + line.p2.x) / 2, (line.p1.y + line.p2.y) / 2);
		float len = b2Vec2(line.p2.x - line.p1.x, line.p2.y - line.p1.y).Length();
		bodyDef.position.Set(pos.x, pos.y);

		b2Body *body = mWorld->CreateBody(&bodyDef);

		//b2PolygonShape dynamicBox;
		//dynamicBox.SetAsBox(len, len);
		b2EdgeShape dynamicBox;
		dynamicBox.Set(b2Vec2(line.p1.x,line.p1.y),b2Vec2(line.p2.x,line.p2.y));


		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 0.5f; // bounce

		body->CreateFixture(&fixtureDef);
		mBoxes.push_back(body);

		/*
		Line2 line = addLines[i];
		float len = b2Vec2(line.p2.x - line.p1.x, line.p2.y - line.p1.y).Length();
		b2Vec2 pos =b2Vec2((line.p1.x + line.p2.x) / 2, (line.p1.y + line.p2.y) / 2);
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.angle = 0;

		b2Body *body = physWorld->CreateBody(&bodyDef);

			//Make the edge Shape
		b2FixtureDef fixtureDef;

		//set density
		fixtureDef.density = 0;
		fixtureDef.restitution = 0;
		fixtureDef.friction = 0.5;

		b2EdgeShape es;
		es.Set(line.p1,line.p2);
		fixtureDef.shape = &es;
		body->CreateFixture(&fixtureDef);
		//Dispose of the shape? look into this to maek sure its good
		//fixtureDef.shape.dispose();

		//body.SetTransform(pos.x, pos.y, atan2(line.p2.y - line.p1.y, line.p2.x - line.p1.x))
			//ADD TO THE PHYSICS WORLD LIST THING

			*/

	}
	
	return addLines;
}

//utilitiy functions
int LazyWorld::getBlockWidth() { return WORLD_WIDTH_BLOCK; }
int LazyWorld::getBlockHeight() { return WORLD_HEIGHT_BLOCK; }
double LazyWorld::getBlockScale() { return WORLD_SCALE_BLOCK; }

LazyWorld::~LazyWorld()
{

}
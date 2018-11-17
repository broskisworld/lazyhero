#include <iostream>
#include <vector>

using namespace std;

#include "World.h"
World::World()
{
	//instantiate vars
	for (int x = 0; x < WORLD_WIDTH_BLOCK; x++)
	{
		worldData.push_back(new vector<Block>(y, new Block());	//Fill 
	}
}

void World::buildLevel0()
{
	//one-time level constructor
	//hard coded in blocks and entities

	//Instantiate all blocks to air
	for (int x = 0; x < WORLD_WIDTH_BLOCK; x++)
		for (int y = 0; y < WORLD_HEIGHT_BLOCK; y++)
			worldData[x][y] = new Block(0);

	//CREATE BLOCKS FOR LEVEL

	//CREATE ENTITIES

	//generate box2d physics objects from list of blocks
	createWorldFromList();

	//generate box2d physics objects for entities (or have entities self call that)
}

Block World::getBlockAt(int x, int y)
{
	return worldData[x][y];
}

void World::createWorldFromList() {
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
				if (getBlockAt(i, j + 1).type == 0 && (j + 1) < WORLD_HEIGHT_BLOCK)
				{
					//start a loop that will keep going to the right we will later adjust the i index
					bool keepGoing = true;
					int startIndex = i;
					int currIndex = i;
					int endIndex = i;
					while (keepGoing && currIndex < WORLD_WIDTH_BLOCK) 
					{

						if (getBlockAt(currIndex, j + 1).type == 0)
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
					Line line;
					line.p1.x = startIndex + -0.5 * WORLD_SCALE_BLOCK;
					line.p1.y = j + 0.5 * WORLD_SCALE_BLOCK;
					line.p2.x = endIndex + 0.5 * WORLD_SCALE_BLOCK;
					line.p2.y = j + 0.5 * WORLD_SCALE_BLOCK;
					addLines.push_back(line);
					//add to line list
					i = endIndex;

				}
				else if (getBlockAt(i, j - 1).type == 0 && (j - 1) > 0) 
				{
					bool keepGoing = true;
					int startIndex = i;
					int currIndex = i;
					int endIndex = i;
					while (keepGoing && currIndex < WORLD_WIDTH_BLOCK)
					{

						if (getBlockAt(currIndex, j - 1).type == 0)
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
					Line line;
					line.p1.x = startIndex + -0.5 * WORLD_SCALE_BLOCK;
					line.p1.y = j - 0.5 * WORLD_SCALE_BLOCK;
					line.p2.x = endIndex + 0.5 * WORLD_SCALE_BLOCK;
					line.p2.y = j - 0.5 * WORLD_SCALE_BLOCK;
					addLines.push_back(line);
					//add to line list
					i = endIndex;
			
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
				if (getBlockAt(j - 1, i) == 0 && j - 1 > 0)
				{
					bool keepGoing = true;
					int startIndex = i;
					int currIndex = i;
					int endIndex = i;
					while (keepGoing && currIndex < WORLD_HEIGHT_BLOCK)
					{

						if (getBlockAt(j - 1, currIndex).type == 0)
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
					Line line;
					line.p1.x = j + -0.5 * WORLD_SCALE_BLOCK;
					line.p1.y = startIndex - 0.5 * WORLD_SCALE_BLOCK;
					line.p2.x = j + -0.5 * WORLD_SCALE_BLOCK;
					line.p2.y = endIndex + 0.5 * WORLD_SCALE_BLOCK;
					addLines.push_back(line);
					//add to line list
					i = endIndex;
				}
				else if (getBlockAt(j + 1, i) == 0 && j + 1 < WORLD_WIDTH_BLOCK)
				{
					bool keepGoing = true;
					int startIndex = i;
					int currIndex = i;
					int endIndex = i;
					while (keepGoing && currIndex < WORLD_HEIGHT_BLOCK)
					{

						if (getBlockAt(j - 1, currIndex).type == 0)
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
					Line line;
					line.p1.x = j + 0.5 * WORLD_SCALE_BLOCK;
					line.p1.y = startIndex - 0.5 * WORLD_SCALE_BLOCK;
					line.p2.x = j + 0.5 * WORLD_SCALE_BLOCK;
					line.p2.y = endIndex + 0.5 * WORLD_SCALE_BLOCK;
					addLines.push_back(line);
					//add to line list
					i = endIndex;
				}
			}
		
		}
	}

	for (int i = 0; i < lines.size; i++) 
	{
		Line line = lines[i]
		float len = new b2Vec2(line.p2.x - line.p1.x, line.p2.y - line.p1.y).Length;
		b2Vec2 pos = new b2Vec2((line.p1.x + line.p2.x) / 2, (line.p1.y + line.p2.y) / 2);
		BodyDef bodyDef = new BodyDef();
		bodyDef.position.set(pos.x, pos.y);
		bodyDef.angle = 0;

		Body body = world.createBody(bodyDef)

			//Make the edge Shape
			FixtureDef fixtureDef = new FixtureDef();
		//set density
		fixtureDef.density = 0;
		fixtureDef.restitution = restitution;
		fixtureDef.friction = 0.5;

		EdgeShape es = new EdgeShape();
		es.set(len / 2f, 0, boxLen / 2f, 0);
		fixture.Def.shape = es;
		body.createFixture(fixtureDef);
		//Dispose of the shape? look into this to maek sure its good
		fixtureDef.shape.dispose();

		body.SetTransform(pos.x, pos.y, atan2(line.p2.y - line.p1.y, line.p2.x - line.p1.x))
			//ADD TO THE PHYSICS WORLD LIST THING

	}

}

//utilitiy functions
int getBlockWidth() { return blockWidth; }
int getBlockHeight() { return blockHeight; }
double getBlockScale() { return blockScale; }
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>

using namespace ci;
using namespace ci::app;

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <time.h>

using namespace std;

#include "LazyWorld.h"
#include "Line.h"
#include "Block.h"
#include "InkMonster.h"

#define HEALTH_INDICATOR_WIDTH 7
#define HEALTH_INDICATOR_HEIGHT 6

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		void *firstUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void *secondUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (firstUserData)
		{
			static_cast<Entity*>(firstUserData)->startContact(static_cast<Entity*>(secondUserData));
		}
		if (secondUserData)
		{
			static_cast<Entity*>(secondUserData)->startContact(static_cast<Entity*>(firstUserData));
		}
	}

	void EndContact(b2Contact* contact) {

		void *firstUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void *secondUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (firstUserData && secondUserData)
		{
			static_cast<Entity*>(firstUserData)->endContact(static_cast<Entity*>(secondUserData));
			static_cast<Entity*>(secondUserData)->endContact(static_cast<Entity*>(firstUserData));
		}
	}
};

LazyWorld::LazyWorld()
{
	//instantiate vars
	//world blocks
	for (int x = 0; x < WORLD_WIDTH_BLOCK; x++)
	{
		Block emptyBlock(0);
		vector<Block> row(WORLD_HEIGHT_BLOCK, emptyBlock);
		worldData.push_back(row);	//Fill 2d vector with air blocks
	}

	//our wonderful lazy hero
	hero = new Hero();
	worldEntities.push_back(/*(Entity *)*/ hero);

	Entity *inkMonster = new InkMonster();
	worldEntities.push_back(inkMonster);

	for (int i = 0; i < NUM_HEALTH_INDICATORS; i++)
	{
		healthIndicators[i].addSpriteSheet({ "Health Indicators.png", HEALTH_INDICATOR_WIDTH, HEALTH_INDICATOR_HEIGHT, 0, 0, 0, 0 });
		healthIndicators[i].addState({ 0, 1, 1, 0, 0 });
		healthIndicators[i].addState({ 1, 1, 1, 1, 0 });
		healthIndicators[i].addState({ 2, 1, 1, 5, 0 });
		healthIndicators[i].setState(0);
	}

	//camera vars
	cam.scale = 40;
	cam.rotation = 0;
	cam.setSlow(10);
	cam.setFixPoint(1500, 1100);

	//reset timers

	deltaRenderTimer.start();
	deltaPhysicsTimer.start();
	srand(time(NULL));
}

Entity *LazyWorld::getHero()
{
	return hero;
}

void LazyWorld::addEntity(Entity *entity)
{
	worldEntities.push_back(entity);
}

b2Vec2 LazyWorld::raycast(b2Vec2 p1, b2Vec2 p2) {
	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1;
	float closestFraction = 1;
	b2Vec2 intersectionNormal(0, 0);
	for (b2Body* b = physWorld->GetBodyList(); b; b = b->GetNext()) 
	{
		for (b2Fixture* f = b ->GetFixtureList(); f; f = f->GetNext()) 
		{
			b2RayCastOutput output;
			if (! f->RayCast(&output, input, 0 ) )
				continue;
			if (output.fraction < closestFraction) {
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}

		}
		
		
	}
	
	b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);
	return intersectionPoint;
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

	//CREATE BLOCKS FOR LEVEL
	
	fillBlocks(0, 50, WORLD_WIDTH_BLOCK - 1, WORLD_HEIGHT_BLOCK - 1,1);
	for (int i = 0; i < 8; i++) {
		fillBlocks(0 + (i * 3 + 1), 50 - (i + 1), WORLD_WIDTH_BLOCK - (i * 3 + 1), 50, 1);
	}
	fillBlocks(0, 1, 0, WORLD_HEIGHT_BLOCK - 1,1);
	fillBlocks(WORLD_WIDTH_BLOCK - 1, 1, WORLD_WIDTH_BLOCK - 1, WORLD_HEIGHT_BLOCK - 1,1);

	fillBlocks(45, 38, 50, 49, 1); 
	fillBlocks(60, 30, 65, 49, 1);
	fillBlocks(70, 25, 79, 49, 1);

	/*for (int i = 0; i < WORLD_WIDTH_BLOCK - 2; i++) {
		double test = sin(i) + 2;
		worldData[i][(int)round(test * 20)].type = 1;
	}*/
	worldData[45][10].type = 1;
	worldData[46][10].type = 1;

	worldData[80][10].type = 1;
	worldData[45][34].type = 1;

	//CREATE ENTITIES
	//place hero in correct location

	//generate box2d physics objects from list of blocks
	//createWorldFromList();

	//generate box2d physics objects for entities (or have entities self call that)
}

b2World* LazyWorld::getB2World() {
	return physWorld;
}

void LazyWorld::createTestBox(double x, double y)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x, y);

	b2Body *body = physWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5, 0.5);	//TEST BOX SIDE LENGTH IS 10

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f; // bounce

	body->CreateFixture(&fixtureDef);
	physicsBodies.push_back(body);
}

Block LazyWorld::getBlockAt(int x, int y)
{
	return worldData[x][y];
}
void LazyWorld::setBlockAt(int x, int y, int type) {
	worldData[x][y].type = type;
}
void LazyWorld::fillBlocks(int x1, int y1, int x2, int y2, int type) {
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			setBlockAt(i, j, type);
		}
	}
}

void LazyWorld::initPhysics()
{
	//init gravity
	b2Vec2 gravity(0.0f, 0.05f);

	//create world
	physWorld = new b2World(gravity);
	physWorld->SetContactListener(new MyContactListener);

	for (int i = 0; i < worldEntities.size(); i++)
		worldEntities[i]->initPhysics();
}

void LazyWorld::stepPhysics()
{
	//delta t
	deltaPhysics = deltaPhysicsTimer.getSeconds();
	deltaPhysicsTimer.stop();
	deltaPhysicsTimer.start();

	//console() << deltaPhysics;

	for (int i = 0; i < worldEntities.size(); i++) {
		worldEntities[i]->physics();
		//nothing
	}

	for (int i = 0; i < 10; ++i)
		physWorld->Step(1/30.0f, 10, 10);
}

void LazyWorld::stepAI()
{
	//iterate through all ai's
	for (int i = 0; i < worldEntities.size(); i++)
		worldEntities[i]->ai();
}

void LazyWorld::render()
{
	//get delta t
	deltaRender = deltaRenderTimer.getSeconds();
	deltaRenderTimer.stop();
	deltaRenderTimer.start();

	//update camera
	cam.update();
	gl::clear(ColorA(0.6f, 0.6f, 0.6f));

	//fill screen w color
	//gl::color(0.6, 0.6f, 0.6f);

	//Camera
	gl::pushMatrices();
	gl::translate(cam.pos);

	gl::translate(vec2(getWindowWidth() / 2, getWindowHeight() / 2));
	gl::scale(vec2(cam.scale, cam.scale));

	gl::rotate(cam.rotation);


	//Render Blocks
	//Find which blocks are on screen or slightly outside of screen (don't waste time drawing everything on the map)
	//getBlockAt(round(getWindowWidth() / cam.scale), (getWindowHeight() / cam.scale));
	vec2 b = cam.camToWorldPos(vec2(0, 0));
	int bWidth = round(getWindowWidth() / cam.scale);
	int bHeight = round(getWindowHeight() / cam.scale);
	vec2 v = cam.camToWorldPos(vec2(0, 0));
	int startX = round(b.x);
	int startY = round(b.y);
	int endX = startX + bWidth + 1;
	int endY = startY + bHeight + 1;
	if (startX < 0) {
		startX = 0;
	}
	if (startY < 0) {
		startY = 0;
	}
	if (endX >= WORLD_WIDTH_BLOCK) {
		endX = WORLD_WIDTH_BLOCK - 1;
	}
	if (endY >= WORLD_HEIGHT_BLOCK) {
		endY = WORLD_HEIGHT_BLOCK - 1;
	}
	
	//End of camera
	//TODO: MUST REMOVE ONCE ENTITY TEXTURES EXIST (why?)
	/*for (const auto &box : physicsBodies) {
		gl::pushModelMatrix();
		gl::translate(box->GetPosition().x, box->GetPosition().y);
		gl::rotate(box->GetAngle());

		gl::drawSolidRect(Rectf(-0.5, -0.5, 0.5, 0.5));	//BOX SIZE

		gl::popModelMatrix();
	}*/

	//iterate through entities and draw
	for (int i = 0; i < worldEntities.size(); i++)
	{
		gl::pushMatrices();
		gl::translate(vec2(worldEntities[i]->entityBody->GetPosition().x,worldEntities[i]->entityBody->GetPosition().y));
		
		//l::drawSolidRect(Rectf(vec2(-0.5, -1), vec2(0.5, 1)));
		
		worldEntities[i]->draw();
		gl::popMatrices();
	}

	//draw block outlines
	gl::pushModelMatrix();
	//gl::translate(lines[0].p1.x + -100, lines[0].p1.y + 100);
	for (int i = 0; i < blockOutlines.size(); i++) {
		Line2 line = blockOutlines[i];
		//cout << line.p1.x;
		gl::color(Color(0, 1, 1));
		vec2 p1(line.p1.x, line.p1.y);
		vec2 p2(line.p2.x, line.p2.y);
		gl::drawLine(p1, p2);
	}
	gl::popModelMatrix();

	gl::popModelMatrix();

	//health bar
	gl::pushMatrices();

	for (int i = 0; i < NUM_HEALTH_INDICATORS; i++)
	{
		float indicatorSize = 10.0;
		float windowEdgeOffset = 20.0;
		float healthIncrement = 100.0 / NUM_HEALTH_INDICATORS;
		float health = hero->getHealth();
		gl::setMatricesWindow(getWindowSize());
		gl::translate(getWindowCenter().x - getWindowBounds().getWidth() / 2, getWindowCenter().y + getWindowBounds().getHeight() / 2);
		gl::translate(windowEdgeOffset + 3 * indicatorSize * i, -windowEdgeOffset);
		gl::scale(indicatorSize, indicatorSize);
		if (health <= healthIncrement * i)
		{
			healthIndicators[i].setState(2);
		}
		else if (health <= healthIncrement * i + healthIncrement / 2)
		{
			healthIndicators[i].setState(1);
		}
		else
		{
			healthIndicators[i].setState(0);
		}
		healthIndicators[i].draw();
	}
	gl::popMatrices();
}

vector<Line2> LazyWorld::createWorldFromList() {
	vector<Line2> addLines;
	//Run a for loop for a horizontal adding of lines
	for (int j = 0; j < WORLD_HEIGHT_BLOCK; j++)
	{
		for (int i = 0; i < WORLD_WIDTH_BLOCK; i++)
		{
			//TODO ight need to take out this littl epart with the currBlock and just test the block using the getBlock function
				//currBlock = getBlockAt(i, j);
			if (getBlockAt(i, j).type != 0)
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
			}
		}
	}
	for (int j = 0; j < WORLD_HEIGHT_BLOCK; j++)
	{
		for (int i = 0; i < WORLD_WIDTH_BLOCK; i++)
		{
			//TODO might need to take out this littl epart with the currBlock and just test the block using the getBlock function
				//currBlock = getBlockAt(i, j);
			if (getBlockAt(i, j).type != 0)
			{
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

			if (getBlockAt(j, i).type != 0)
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
			}
		}
	}
	for (int j = 0; j < WORLD_WIDTH_BLOCK; j++)
	{
		for (int i = 0; i < WORLD_HEIGHT_BLOCK; i++)
		{
			//currBlock = getBlockAt(j, i);

			if (getBlockAt(j, i).type != 0)
			{
				if (j + 1 < WORLD_WIDTH_BLOCK) {
					if (getBlockAt(j + 1, i).type == 0)
					{
						bool keepGoing = true;
						int startIndex = i;
						int currIndex = i;
						int endIndex = i;
						while (keepGoing && currIndex < WORLD_HEIGHT_BLOCK)
						{

							if (getBlockAt(j + 1, currIndex).type == 0 && getBlockAt(j, currIndex).type != 0)
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

		b2Body *body = physWorld->CreateBody(&bodyDef);

		//b2PolygonShape dynamicBox;
		//dynamicBox.SetAsBox(len, len);
		b2EdgeShape dynamicBox;
		dynamicBox.Set(b2Vec2(line.p1.x,line.p1.y),b2Vec2(line.p2.x,line.p2.y));


		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.7f;
		fixtureDef.restitution = 0.1f; // bounce

		body->CreateFixture(&fixtureDef);
		physicsBodies.push_back(body);

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
	
	blockOutlines = addLines;

	return addLines;	//deprecated
}

//utilitiy functions
int LazyWorld::getBlockWidth() { return WORLD_WIDTH_BLOCK; }
int LazyWorld::getBlockHeight() { return WORLD_HEIGHT_BLOCK; }
double LazyWorld::getBlockScale() { return WORLD_SCALE_BLOCK; }
void LazyWorld::addPhysicsBody(b2Body * newPhysBody) { physicsBodies.push_back(newPhysBody); }
float LazyWorld::getDeltaRender() {return deltaRender; }
float LazyWorld::getDeltaPhysics() { return deltaPhysics; }

LazyWorld::~LazyWorld()
{

}
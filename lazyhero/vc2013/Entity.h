#pragma once

#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <Box2D/Box2D.h>

using namespace std;
using namespace ci;
using namespace ci::app;

#include "LazyWorld.h"

//default entity attributes
#define ENTITY_DEFAULT_HEALTH 10.0f
#define ENTITY_DEFAULT_BOUNDING_HEIGHT 1
#define ENTITY_DEFAULT_BOUNDING_WIDTH 0.5f
#define ENTITY_DEFAULT_SPAWN_X 50
#define ENTITY_DEFAULT_SPAWN_Y 20

class Entity
{
protected:
	float health;
	float maxHP;
	int entityColliderType;
	b2Body* entityBody;
public:
	//physics
	b2Vec2 startPos;
	b2PolygonShape boundingBox;
	int collideWithWhat;
	int contacting;
	
	Entity();

	void initPhysics();	//must be called after world init

	virtual void ai();
	virtual void physics();
	virtual void draw();

	virtual void startContact(b2Fixture * contactingFixture, Entity *contactingEntity);
	virtual void endContact(b2Fixture * contactingFixture, Entity *contactingEntity);

	b2Body * getB2Body() { return entityBody; }
	b2Vec2 getVectorToEntity(Entity* targetEntity);
	
	void setHealth(float newHealth);
	void changeHealth(float deltaHealth);
	float getHealth();
	float getMaxHealth();

	~Entity();
};
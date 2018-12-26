#include <iostream>
#include <Box2D/Box2D.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
using namespace std;

#include "LazyWorld.h"
#include "Entity.h"

extern LazyWorld gameWorld;

using namespace ci;
using namespace ci::app;

enum _entityCategory {
	BOUNDARY = 0x0001,
	ENTITY = 0x0002,
	HERO = 0x0004,
	ENTITY_COLLIDER = 0x0008,
	SENSOR = 0x0010,
};

Entity::Entity()
{
	startPos.x = 50;	//start pos
	startPos.y = 20;
}

void Entity::initPhysics() {
	b2World * physWorld = gameWorld.getB2World();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(startPos.x, startPos.y);

	entityBody = physWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5, 1);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//Makes it so it won't rotate
	//fixtureDef.density = 0.0f
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.0f; // bounce

	entityBody->CreateFixture(&fixtureDef);
	
	fixtureDef.filter.categoryBits = ENTITY;
	fixtureDef.filter.maskBits = BOUNDARY | HERO;
	
	gameWorld.addPhysicsBody(entityBody);
}

void Entity::ai() {
	//override this function :)
}

void Entity::physics() {
	//override this function :)
}

void Entity::draw() {
	//override this function :)
}

Entity::~Entity() {
	gameWorld.getB2World()->DestroyBody(entityBody);	//delete physics body
}
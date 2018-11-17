#include <iostream>
#include <Box2D/Box2D.h>
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
	dynamicBox.SetAsBox(1, 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//Makes it so it won't rotate
	//fixtureDef.density = 0.0f
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f; // bounce

	entityBody->CreateFixture(&fixtureDef);
	
	fixtureDef.filter.categoryBits = ENTITY;
	fixtureDef.filter.maskBits = BOUNDARY | HERO;
	
	gameWorld.addPhysicsBody(entityBody);	//add to render n shit

	/*
	//Create the hitbox
	b2PolygonShape hitBox;
	hitBox.SetAsBox(0.7, 0.3);
	b2FixtureDef sensorDef;
	sensorDef.shape = &hitBox;
	sensorDef.isSensor = true;
	sensorDef.filter.categoryBits = SENSOR;
	sensorDef.filter.maskBits = BOUNDARY;
	body->CreateFixture(&sensorDef);
	*/
}

void Entity::ai() {
	//console() << "ENTITY XY\t" << entityBody->GetPosition().x << ", " << entityBody->GetPosition().y << endl;
	console() << "ENTITY" << endl;
}
void Entity::physics() {

}

void Entity::draw() {

}
Entity::~Entity() {

}
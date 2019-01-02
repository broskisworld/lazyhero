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

#define CONTACT_HEALTH_DECREMENT 1

Entity::Entity()
{
	//default entity spawn
	startPos.x = ENTITY_DEFAULT_SPAWN_X;	//start pos
	startPos.y = ENTITY_DEFAULT_SPAWN_Y;

	//default bounding box
	boundingBox.SetAsBox(ENTITY_DEFAULT_BOUNDING_WIDTH, ENTITY_DEFAULT_BOUNDING_HEIGHT);	//width: 1 height: 1

	//colliders
	entityColliderType = COLLIDER_ENTITY;
	collideWithWhat = COLLIDER_WORLD | COLLIDER_ENTITY | COLLIDER_ENEMY | COLLIDER_BULLET;
	contacting = 0;

	maxHP = ENTITY_DEFAULT_HEALTH;
	health = maxHP;
}

void Entity::initPhysics()
{
	b2World * physWorld = gameWorld.getB2World();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(startPos.x, startPos.y);

	entityBody = physWorld->CreateBody(&bodyDef);

	entityBody->SetUserData(this);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boundingBox;
	//Makes it so it won't rotate
	//fixtureDef.density = 0.0f
	fixtureDef.friction = 0.1f;
	fixtureDef.restitution = 0.0f; // bounce

	fixtureDef.filter.categoryBits = entityColliderType;
	fixtureDef.filter.maskBits = collideWithWhat;

	entityBody->CreateFixture(&fixtureDef);
	
	gameWorld.addPhysicsBody(entityBody);
}

void Entity::ai() {
	//override this function :)

	//example death sequence:
	//if (health <= 0.0f)
	//{
	//	gameWorld.removeEntity(this);
	//}
}

void Entity::physics() {
	//override this function :)
}

void Entity::draw() {
	//override this function :)
}

void Entity::startContact(b2Fixture * contactingFixture, Entity *contactingEntity)
{
	if (contactingEntity != NULL)
	{
		;//is entity
	}

	contacting++;
}

void Entity::endContact(b2Fixture * contactingFixture, Entity *contactingEntity)
{
	if (contactingEntity != NULL)
	{
		;//is entity
	}

	contacting--;
}

b2Vec2 Entity::getVectorToEntity(Entity* targetEntity)
{
	b2Vec2 myPosition = entityBody->GetPosition();
	b2Vec2 targetPosition = targetEntity->entityBody->GetPosition();
	return targetPosition - myPosition;
}

void Entity::setHealth(float newHealth)
{
	health = newHealth;
}

void Entity::changeHealth(float deltaHealth)
{
	health += deltaHealth;
}

float Entity::getHealth()
{
	return health;
}

float Entity::getMaxHealth()
{
	return maxHP;
}

Entity::~Entity() {
	gameWorld.getB2World()->DestroyBody(entityBody);	//delete physics body
}
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
	//console() << "ENTITY" << endl;
}

void Entity::physics() {

}

void Entity::draw() {
	/*
	subFrame++;
	if (subFrame > 10) {
		currentFrame++;
		subFrame = 0;
	}
	*/
	
	//TODO: clean up and consolodate animation drawing code into an Animation class that can be used anywhere

	/*if (!mTexture)
	{
		auto img = loadImage(loadAsset(entSpriteSheet.textureName));	//BUG: crashes automatically if asset not found??
		mTexture = gl::Texture2d::create(img);

		if(!mTexture)	//^^^making this code useless and redundant (kinda pointless in the first place tho)
			return;	//notexture
	}
	timeSinceLastFrame = timeSinceLastFrame + gameWorld.getDeltaRender();
	if ((1 / currentAnimation.fps) < timeSinceLastFrame) {
		timeSinceLastFrame = 0;
		currentFrame++;
	}

	if (currentFrame + 1 > currentAnimation.numFrames) {
		currentFrame = 0;
	}
	
	mTexture->setMagFilter(GL_NEAREST); // disable multi-sample if >= 100%
	mTexture->setMinFilter(GL_LINEAR); // enable multi-sampling if < 100%
	//vec2 tPos2(1 / mTexture->getActualWidth() * (currentAnimation.width * frame), 1 / mTexture->getActualHeight() * (currentAnimation.height * frame));
	
	Rectf destRect{ -1.5,-1.5, 1, 1 };
	if (flip) {
		destRect = { -1,-1.5,1.5,1 };
	}
	int x = currentAnimation.width * (currentFrame + 1) + currentAnimation.frameOffsetX * currentAnimation.width + entSpriteSheet.paddingLeft;
	int y = currentAnimation.height + currentAnimation.frameOffsetY * currentAnimation.height + entSpriteSheet.paddingTop;
	//console() << currentFrame << endl;
	//console() << currentFrame << endl;
	if (x > mTexture->getActualWidth() - entSpriteSheet.paddingRight) {
		//y = currentAnimation.height + (x / (mTexture->getActualWidth() - currentSpriteSheet.paddingRight)) * currentAnimation.height;

		//console() << (x / (mTexture->getActualWidth() - entSpriteSheet.paddingRight)) << endl;
		//console() << x << endl;
		x = x % (mTexture->getActualWidth() - entSpriteSheet.paddingRight) + entSpriteSheet.paddingLeft;
		//console() << x << endl;

		y = y + currentAnimation.height;
	}

	//bounding box test by tj?
	Area sourceArea{ x - currentAnimation.width, y - currentAnimation.height, x, y };
	Rectf uvs = mTexture->getAreaTexCoords(sourceArea);

	gl::ScopedGlslProg shader(gl::getStockShader(gl::ShaderDef().texture(mTexture)));
	gl::ScopedTextureBind tex0(mTexture);
	if (!flip) {
		gl::drawSolidRect(destRect, uvs.getUpperLeft(), uvs.getLowerRight());
	}
	else {
		gl::drawSolidRect(destRect, uvs.getUpperRight(), uvs.getLowerLeft());
	}
}

b2Vec2 Entity::getVectorToEntity(Entity* targetEntity)
{
	b2Vec2 myPosition = entityBody->GetPosition();
	b2Vec2 targetPosition = targetEntity->entityBody->GetPosition();
	return targetPosition - myPosition;
}

Entity::~Entity() {

}
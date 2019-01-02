#pragma once

#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <Box2D/Box2D.h>

typedef struct {
	std::string filename;

	int frameWidth;
	int frameHeight;
	
	int paddingLeft;
	int paddingRight;
	int paddingTop;
	int paddingBottom;
}spriteSheet;

typedef struct {
	int id;

	int numFrames;
	float fps;
	bool repeat;

	int frameOffsetX;
	int frameOffsetY;
}animationDescription;

class Animation
{
	spriteSheet defaultSpriteSheet;
	ci::gl::Texture2dRef spriteSheetTexture;

	std::vector<animationDescription> animStates;
	
	size_t curAnimState;	//by index in vector NOT by animStates.id value (for internal use only)
	int curFrame;
	double timeSinceLastFrame;
	bool animationFinished;
public:
	//constructor
	Animation();
	Animation(spriteSheet _defaultSpriteSheet);

	int addSpriteSheet(spriteSheet newSpriteSheet);	//TODO: multiple sprite sheet support? - returns 0 if succesful
	int addState(animationDescription desc);	//add new animation state - returns 0 if succesful

	void draw();

	//utility
	bool mirror;	//flip image in X direction?

	int getState();	//returns current id of state being used
	int setState(int newStateID);	//sets current state to id given - returns 0 if successful
	bool isFinished();	//if non-repeating animation, return whether animation is complete

	//destructor
	~Animation();
};
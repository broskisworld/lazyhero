//std includes
#include <iostream>

//SDK
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <Box2D/Box2D.h>

//local includes
#include "LazyWorld.h"
#include "Animation.h"

using namespace std;
using namespace ci;
using namespace ci::app;

extern LazyWorld gameWorld;

Animation::Animation()
{
	curAnimState = 0;
	curFrame = 0;
	timeSinceLastFrame = 0.0;

	mirror = false;

	animationFinished = false;
}

Animation::Animation(spriteSheet _defaultSpriteSheet)
{
	addSpriteSheet(_defaultSpriteSheet);

	curAnimState = 0;
	curFrame = 0;
	timeSinceLastFrame = 0.0;

	mirror = false;

	animationFinished = false;
}

int Animation::addSpriteSheet(spriteSheet newSpriteSheet)
{
	//load texture
	/*try
	{
		auto spriteSheetImage = loadImage(loadAsset(newSpriteSheet.filename));	//attempt to locate file
		spriteSheetTexture = gl::Texture2d::create(spriteSheetImage);

		if (!spriteSheetTexture)
		{
			console() << "No texture created from file \"" << newSpriteSheet.filename << "\" - GL error?" << endl;	//TODO: auto display purple texture in replacement
		
			return 2;
		}
	}
	catch(AssetLoadExc e)
	{
		console() << "Error loading spritesheet texture from file \"" << newSpriteSheet.filename << "\": " << e.what() << endl;

		return 1;	//fail
	}*/

	defaultSpriteSheet = newSpriteSheet;	//update spritesheet description

	return 0;	//success
}

int Animation::addState(animationDescription desc)
{
	for (int i = 0; i < animStates.size(); i++)	//check for duplicate ids
		if (desc.id == animStates[i].id)
			return 1;	//do not allow animations with the same id (use enums for state type)

	animStates.push_back(desc);	//else add animation type

	return 0;
}

void Animation::draw()
{
	if (!spriteSheetTexture)
	{
		//load texture
		try
		{
			auto spriteSheetImage = loadImage(loadAsset(defaultSpriteSheet.filename));	//attempt to locate file
			spriteSheetTexture = gl::Texture2d::create(spriteSheetImage);

			if (!spriteSheetTexture)
			{
				console() << "No texture created from file \"" << defaultSpriteSheet.filename << "\" - GL error?" << endl;	//TODO: auto display purple texture in replacement

				return;
			}
		}
		catch (AssetLoadExc e)
		{
			console() << "Error loading spritesheet texture from file \"" << defaultSpriteSheet.filename << "\": " << e.what() << endl;

			return;	//fail
		}
	}

	if (animationFinished)
		return;

	//update timeSinceLastFrame
	timeSinceLastFrame += gameWorld.getDeltaRender();

	//has timeSinceLastFrame elapsed the time per frame?
	if ((1.0 / animStates[curAnimState].fps) < timeSinceLastFrame)
	{
		//timeSinceLastFrame -= (1.0 / animStates[curAnimState].fps);	//reset timeSinceLastFrame
		timeSinceLastFrame = 0.0;
		
		//curFrame = (curFrame + 1) % animStates[curAnimState].numFrames;	//increment frame & wrap if necessary
		curFrame++;
	}

	if ((curFrame + 1) > animStates[curAnimState].numFrames)
	{
		if (animStates[curAnimState].repeat)
		{
			curFrame = 0;
		}
		else
		{
			animationFinished = true;
		}
	}

	//not quite sure what this does...
	spriteSheetTexture->setMagFilter(GL_NEAREST); // disable multi-sample if >= 100%
	spriteSheetTexture->setMinFilter(GL_LINEAR);	// enable multi-sampling if < 100%

	//src texture rectangle (top left points)
	/*int srcXOffsetNonWrapped = ((curFrame * defaultSpriteSheet.frameWidth) +
		(animStates[curAnimState].frameOffsetX * defaultSpriteSheet.frameWidth) +
		defaultSpriteSheet.paddingLeft);
	int spriteSheetWrapPoint = (spriteSheetTexture->getActualWidth() - defaultSpriteSheet.paddingBottom);
	
	int srcX = srcXOffsetNonWrapped % spriteSheetWrapPoint;
	int srcY = ((srcXOffsetNonWrapped / spriteSheetWrapPoint) * defaultSpriteSheet.frameHeight) +
		(animStates[curAnimState].frameOffsetY * defaultSpriteSheet.frameHeight) +
		defaultSpriteSheet.paddingTop;*/
	int srcX = (defaultSpriteSheet.frameWidth * (curFrame + 1)) + (animStates[curAnimState].frameOffsetX * defaultSpriteSheet.frameWidth) + defaultSpriteSheet.paddingLeft;
	int srcY = defaultSpriteSheet.frameHeight + (animStates[curAnimState].frameOffsetY * defaultSpriteSheet.frameHeight) + defaultSpriteSheet.paddingTop;
	//console() << currentFrame << endl;
	//console() << currentFrame << endl;
	if (srcX > spriteSheetTexture->getActualWidth() - defaultSpriteSheet.paddingRight) {
		//y = currentAnimation.height + (x / (mTexture->getActualWidth() - currentSpriteSheet.paddingRight)) * currentAnimation.height;

		//console() << (x / (mTexture->getActualWidth() - entSpriteSheet.paddingRight)) << endl;
		//console() << x << endl;
		srcX = srcX % (spriteSheetTexture->getActualWidth() - defaultSpriteSheet.paddingRight) + defaultSpriteSheet.paddingLeft;
		//console() << x << endl;

		srcY = srcY + defaultSpriteSheet.frameHeight;
	}

	//Area sourceArea{ srcX, srcY, srcX + defaultSpriteSheet.frameWidth, srcY + defaultSpriteSheet.frameHeight };	//top left, to bottom right
	Area sourceArea{ srcX - defaultSpriteSheet.frameWidth, srcY - defaultSpriteSheet.frameHeight, srcX, srcY };
	Rectf uvs = spriteSheetTexture->getAreaTexCoords(sourceArea);
	
	//Now draw the actual sprite
	gl::ScopedGlslProg shader(gl::getStockShader(gl::ShaderDef().texture(spriteSheetTexture)));
	gl::ScopedTextureBind tex0(spriteSheetTexture);
	
	Rectf destRect;
	if (mirror)
	{
		//destRect = { -1.5,-1.5, 1, 1 };
		destRect = { -1,-1.5,1.5,1 };
		gl::drawSolidRect(destRect, uvs.getUpperRight(), uvs.getLowerLeft());
	}
	else
	{
		//destRect = { -1,-1.5,1.5,1 };
		destRect = { -1.5,-1.5, 1, 1 };
		gl::drawSolidRect(destRect, uvs.getUpperLeft(), uvs.getLowerRight());
	}
}

int Animation::getState()
{
	return animStates[curAnimState].id;
}

int Animation::setState(int newStateID)
{
	if (newStateID == animStates[curAnimState].id)
		return 0;

	animationFinished = false;

	for (int i = 0; i < animStates.size(); i++)
		if (animStates[i].id == newStateID)
		{
			curAnimState = i;
			curFrame = 0;

			return 0;
		}

	return 1;	//no matching state!
}

bool Animation::isFinished()
{
	return animationFinished;
}

Animation::~Animation()
{

}
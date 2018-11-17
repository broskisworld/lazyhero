#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>

#include "LazyWorld.h"
#include "Line.h"
#include "Game.h"
#include "GodController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

LazyWorld gameWorld;
GodController godInput;
gameState curGameState;


class lazyheroApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void keyDown(KeyEvent event) override;
	void keyUp(KeyEvent event) override;
	void update() override;
	void draw() override;
};

void lazyheroApp::setup()
{
	curGameState = SETUP;

	gameWorld.initPhysics();
	
	//build world
	gameWorld.buildLevel0();
	gameWorld.createWorldFromList();
	
	curGameState = RUNNING;
}

void lazyheroApp::mouseDown(MouseEvent event)
{
	if (curGameState == RUNNING) {
		//vec2 v = gameWorld.cam.camToWorldPos(vec2(event.getPos().x, event.getPos().y));
		//gameWorld.createTestBox(v.x,v.y);
		//vec2 v2 = gameWorld.cam.worldToCamPos(vec2(event.getPos().x, event.getPos().y));
		//gameWorld.cam.setFixPoint(v.x * gameWorld.cam.scale,v.y * gameWorld.cam.scale);
	}
}

void lazyheroApp::keyDown(KeyEvent event)
{
	switch (event.getChar())
	{
	case 'w':
		godInput.forceRevelation(JUMP);
		break;
	case 'a':
		godInput.forceRevelation(GO_LEFT);
		break;
	case 'd':
		godInput.forceRevelation(GO_RIGHT);
		break;
	default:
		//godInput.forceRevelation(NO_REVELATION);
		break;
	}
}

void lazyheroApp::keyUp(KeyEvent event)
{
	switch (event.getChar())
	{
	case 'w':
		if (godInput.getRevelation() == JUMP)
			godInput.forceRevelation(NO_REVELATION);
		break;
	case 'a':
		if (godInput.getRevelation() == JUMP)
			godInput.forceRevelation(NO_REVELATION);
		break;
	case 'd':
		if (godInput.getRevelation() == JUMP)
			godInput.forceRevelation(NO_REVELATION);
		break;
	default:
		//godInput.forceRevelation(NO_REVELATION);
		break;
	}
}

void lazyheroApp::update()
{
	if (curGameState == RUNNING)
	{
		//run ai
		gameWorld.stepAI();

		//run physics
		gameWorld.stepPhysics();
	}
}

void lazyheroApp::draw()
{
	if (curGameState == RUNNING)
		gameWorld.render();
}

CINDER_APP( lazyheroApp, RendererGl )

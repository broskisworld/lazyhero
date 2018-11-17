#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>

#include "LazyWorld.h"
#include "Line.h"
#include "Game.h"

using namespace ci;
using namespace ci::app;
using namespace std;

LazyWorld gameWorld;
gameState curGameState;


class lazyheroApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
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
		vec2 v = gameWorld.cam.camToWorldPos(vec2(event.getPos().x, event.getPos().y));
		gameWorld.createTestBox(v.x,v.y);
		//vec2 v2 = gameWorld.cam.worldToCamPos(vec2(event.getPos().x, event.getPos().y));
		gameWorld.cam.setFixPoint(v.x * gameWorld.cam.scale,v.y * gameWorld.cam.scale);
	}
}

void lazyheroApp::update()
{
	if (curGameState == RUNNING)
	{
		//run physics
		gameWorld.stepPhysics();

		//run ai
		gameWorld.stepAI();
	}
}

void lazyheroApp::draw()
{
	if (curGameState == RUNNING)
		gameWorld.render();
}

CINDER_APP( lazyheroApp, RendererGl )

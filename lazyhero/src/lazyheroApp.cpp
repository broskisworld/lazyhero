#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>
#include "LazyWorld.h"
#include "Line.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class lazyheroApp : public App {
	LazyWorld gameWorld;
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void lazyheroApp::setup()
{
	gameWorld.initPhysics();
	
	//build world
	gameWorld.buildLevel0();
	gameWorld.createWorldFromList();
}

void lazyheroApp::mouseDown( MouseEvent event )
{
	gameWorld.createTestBox(event.getPos().x, event.getPos().y);
}

void lazyheroApp::update()
{
	//run physics
	gameWorld.stepPhysics();
	
	//run ai
	gameWorld.stepAI();
}

void lazyheroApp::draw()
{
	gameWorld.render();
}

CINDER_APP( lazyheroApp, RendererGl )

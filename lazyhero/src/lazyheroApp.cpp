#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>
#include "LazyWorld.h"
#include "Line.h"

using namespace ci;
using namespace ci::app;
using namespace std;

const float BOX_SIZE = 10;

class lazyheroApp : public App {
	LazyWorld gameWorld;
	vector<Line2> lines;
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
	
	void addBox( const vec2 &pos );
	
};

void lazyheroApp::setup()
{
	gameWorld.initPhysics();
	gameWorld.buildLevel0();

	lines = gameWorld.createWorldFromList();
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

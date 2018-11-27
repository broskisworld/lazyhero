#pragma once

#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
using namespace ci;
using namespace ci::app;

using namespace std;

class Camera2D
{
	vec2 fixPoint;
	double slow;
	bool looselyFollow;
	public:
		vec2 pos;
		
		double scale;
		double rotation;
		Camera2D();
		void update();
		void setSlow(double set);
		void setFixPoint(double x, double y);
		vec2 camToWorldPos(vec2 v);
		vec2 worldToCamPos(vec2 v);

};
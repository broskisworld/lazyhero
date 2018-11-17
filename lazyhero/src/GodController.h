#pragma once

#include <iostream>

using namespace std;

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../leapc/include/LeapC.h"

using namespace ci;
using namespace ci::app;

typedef enum
{
	GO_LEFT,
	GO_RIGHT,
	JUMP,
	NO_REVELATION
}revelation;

class GodController
{
	revelation curRevelation;
public:
	LEAP_CONNECTION leapConnection;
	LEAP_CONNECTION_CONFIG *leapConfig;
	LEAP_DEVICE_REF leapDeviceList[5];	//only one??
	unsigned int numLeapDevices;

	bool initConnection();
	bool isAlive();
	bool hasRevelation();
	revelation getRevelation();
	void forceRevelation(revelation);
};
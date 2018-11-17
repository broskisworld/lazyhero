#include <iostream>
#

using namespace std;

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;


#include "Game.h"
#include "GodController.h"
#include "../leapc/include/LeapC.h"

bool GodController::initConnection()
{
	leapConfig = nullptr;

	console() << "connecting to LeapC...\n";
	eLeapRS connectionResult = LeapCreateConnection(leapConfig, &leapConnection);
	if (connectionResult != eLeapRS_Success)
	{
		console() << "FAIL!\n" << "connect failed with error " << connectionResult << endl;

		return false;
	}
	console() << "OK!\n";

	numLeapDevices = 0;

	console() << "getting device array..." << endl;
	eLeapRS deviceListResult = LeapGetDeviceList(leapConnection, leapDeviceList, &numLeapDevices);
	if (connectionResult != eLeapRS_Success)
	{
		console() << "FAIL!\n" << "device list failed with error " << deviceListResult << endl;

		return false;
	}
	console() << "OK!\n";

}

bool GodController::isAlive()
{
	return false;
}

bool GodController::hasRevelation()
{
	return (curRevelation != NO_REVELATION);
}

revelation GodController::getRevelation()
{
	return NO_REVELATION;
}

void GodController::forceRevelation(revelation newRevelation)
{
	curRevelation = newRevelation;
}
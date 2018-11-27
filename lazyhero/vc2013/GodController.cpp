#include <iostream>

using namespace std;

#include "Game.h"
#include "GodController.h"

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
	return curRevelation;
}

void GodController::forceRevelation(revelation newRevelation)
{
	curRevelation = newRevelation;
}
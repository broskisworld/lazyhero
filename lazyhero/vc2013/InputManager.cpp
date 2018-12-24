#include <iostream>

using namespace std;

#include "Game.h"
#include "InputManager.h"

//InputManager is descended from GodController (the name made sense with the game we were making before)
//Pretty much all the code from GodController has been made obsolete and replaced with simple boolean values to act as a buffer between enitity AI calls and Cinder's API
//Might end up phasing out InputManager in future updates
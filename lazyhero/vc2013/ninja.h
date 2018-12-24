#pragma once

#include <iostream>
#include <math.h>

using namespace std;

#include "LazyWorld.h"
#include "InputManager.h"
#include "Entity.h"

#define NINJA_STAMINA 1.0	//seconds
#define NINJA_ATTACK_RECHARGE 1.0	//seconds
#define NINJA_ATTACK_DAMAGE 10	//???

typedef enum
{
	IDLE2,
	CHASING,
	ATTACK,
	TELEPORT,
	DIE
}ninjaState;

class ninja : public Entity
{
	ninjaState aiState;
	animation idle, running, attack, die;
public:
	ninja();
	void ai();
	~ninja();
};
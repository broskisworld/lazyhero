#include "ninja.h"

ninja::ninja()
{
	entSpriteSheet = { "ninja-spritemap.png", 35, 0, 0, 0 };

	idle = { 42, 26, 4, 3, 0, 0 };
	running = { 42, 26, 3, 4, 0, 1 };
	attack = { 42, 26, 4, 4, 0, 4 };
	die = { 42, 26, 4, 2, 0, 3 };

	aiState = IDLE2;
}

void ninja::ai()
{
	switch (aiState)
	{
	case IDLE2:
		break;
	case CHASING:
		break;
	case ATTACK:
		break;
	case TELEPORT:
		break;
	case DIE:
		break;
	}
}

ninja::~ninja()
{

}
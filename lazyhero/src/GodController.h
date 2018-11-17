#pragma once

#include <iostream>

using namespace std;

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
	bool isAlive();
	bool hasRevelation();
	revelation getRevelation();
	void forceRevelation(revelation);
};
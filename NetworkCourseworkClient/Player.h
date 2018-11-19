#pragma once
#include "GameObj.h"
class Player: public GameObj
{
public://function declarations
	using GameObj::GameObj;
	void update(float dt);
	void init();

private:
	int speed = 5;
};

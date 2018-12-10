#pragma once
#include "GameObj.h"

class Player: public GameObj
{
public://function declarations
	using GameObj::GameObj;
	void update(float dt);
	void init(float x, float y);

	PlayerStates getState();

private:
	int speed = 5;
	PlayerStates currentState = PlayerStates::stationary;
	bool inAir;
	bool left;//true if facing left, false if facing right
};

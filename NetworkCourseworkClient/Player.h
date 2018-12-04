#pragma once
#include "GameObj.h"

class Player: public GameObj
{
public://function declarations
	using GameObj::GameObj;
	void update(float dt);
	void init();

	PlayerStates getState();

private:
	int speed = 5;
	PlayerStates currentState = PlayerStates::stationary;
	bool inAir;
};

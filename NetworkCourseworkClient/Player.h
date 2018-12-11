#pragma once
#include "GameObj.h"

class Player: public GameObj
{
public://function declarations
	using GameObj::GameObj;
	void update(float dt);
	void init(float x, float y);

	PlayerStates getState();
	ObjectType getType() { return ObjectType::PLAYER; };

	bool inAir;

	bool getShooting() { return isShooting; };
	bool getDir() { return left; }

private:
	void collisionHandle();
	int speed = 5;
	PlayerStates currentState = PlayerStates::stationary;
	bool left;//true if facing left, false if facing right
	bool isShooting;
};

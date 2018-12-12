#pragma once
#include "GameObj.h"

class Player2 : public GameObj
{
public:
	struct Input
	{//struct for the object prediction to gather input
		float pos[2];
		PlayerStates newState;
		bool dir;
		bool newInfo;
		float yVel;
	};

	using GameObj::GameObj;
	void update(float dt);
	void init(float x, float y);

	PlayerStates getState();
	ObjectType getType() { return ObjectType::PLAYER2; };

	bool inAir = false;

	Input input;

private:
	int speed = 5;
	PlayerStates currentState = PlayerStates::stationary;
	bool left;//true if facing left, false if facing right	
	b2Vec2 serverPos;
	float rubberBandSpeed;
	b2Vec2 rubberBandDirection;
	bool prediction = true; // variable to turn prediction on/off
};

/*
	object class to represent where the enemy player is currently at
*/
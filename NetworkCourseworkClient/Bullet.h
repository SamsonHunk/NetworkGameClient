#pragma once
#include "GameObj.h"

class Bullet : public GameObj
{
public:
	using GameObj::GameObj;

	void update(float dt);
	void init(float x, float y);
	void serverAssert(float x, float y);
	ObjectType getType();

	bool dir; //true for left, false for right
	bool awake = false;

	void activate(float x, float y, bool dirIn);
	void deactivate();
	
	bool newBullet = false;
private:
	int speed = 2;
	
};
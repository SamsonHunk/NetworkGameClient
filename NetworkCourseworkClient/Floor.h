#pragma once
#include "GameObj.h"
class Floor: public GameObj
{
public:
	using GameObj::GameObj;
	void update(float dt);
	void init(float x, float y);

private:

};

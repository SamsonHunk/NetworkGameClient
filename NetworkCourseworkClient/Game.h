#pragma once
#include "State.h"
//state for ingame
class Game: public State
{
public:
	Game();
	~Game();

	void init(sf::RenderWindow* windowIn, Input* in);
	void update(float dt);
	void render();
	void deload();

private:

};

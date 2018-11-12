#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include "Input.h"


class State //parent gamestate class, purely virtual
{
public:
	//all the shared virtual functions
	virtual void init(sf::RenderWindow* windowIn, Input* in) = 0; 
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void deload() = 0;
	virtual GameState needsChange() = 0;

protected:
	sf::RenderWindow* window; //pointer to window
	Input* input; //pointer to input manager
};

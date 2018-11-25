#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Box2D.h>
#include "Input.h"
#include "Global.h"
#include <thread>

class State //parent gamestate class, purely virtual
{
public:
	//all the shared virtual functions
	virtual void init(sf::RenderWindow* windowIn, Input* in, sf::UdpSocket* socketIn) = 0; 
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void deload() = 0;
	virtual GameState needsChange() = 0;

protected:
	sf::RenderWindow* window; //pointer to window
	Input* input; //pointer to input manager
	sf::UdpSocket* socket; //pointer to the socket currently being used
};

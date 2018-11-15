#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(sf::RenderWindow * windowIn, Input * in, sf::UdpSocket * socketIn)
{
	window = windowIn;
	input = in;
	socket = socketIn;

	//initialise gameworld gravity
	physicsWorld = new b2World(b2Vec2(0, -9.8));
	
	//setup stage floor
	floor.setPosition(200, 400);
	floor.setFillColor(sf::Color::Red);
	floor.setSize(sf::Vector2f(400, 50));

}

void Game::update(float dt)
{//update game logic
	
}

void Game::render()
{//render stuff
	window->draw(floor);

}

void Game::deload()
{
}

GameState Game::needsChange()
{
	return GameState::NoChange;
}

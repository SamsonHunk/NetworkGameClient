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
	playerTexture = new sf::Texture();

	playerTexture->loadFromFile("image/player.png");

	player = new Player(physicsWorld, playerTexture, input, windowIn);
	player->init();

}

void Game::update(float dt)
{//update game logic
	
	player->update(dt);
	physicsWorld->Step(0.6f, 6, 2);
}

void Game::render()
{//render stuff
	window->draw(floor);
	player->render();
}

void Game::deload()
{
}

GameState Game::needsChange()
{
	return GameState::NoChange;
}

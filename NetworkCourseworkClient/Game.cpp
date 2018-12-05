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
	physicsWorld = new b2World(b2Vec2(0, .5));
	
	//setup stage floor
	floor.setPosition(200, 400);
	floor.setFillColor(sf::Color::Red);
	floor.setSize(sf::Vector2f(400, 50));
	playerTexture = new sf::Texture();
	floorTexture = new sf::Texture();

	playerTexture->loadFromFile("image/player.png");
	floorTexture->loadFromFile("image/floor.png");
	
	serverIp = sf::IpAddress::LocalHost;
	connectionMessage packetOut;
	packetOut.clientIp = "127.0.0.1";
	packetOut.clientPort = 7778;

	outPacket << packetOut.clientIp << packetOut.clientPort;
	if (socket->send(outPacket,serverIp, 7777) != sf::Socket::Done) //connect to server
	{
		//error
	}

	gameFloor = new Floor(physicsWorld, floorTexture, input, windowIn);
	gameFloor->init();

	player = new Player(physicsWorld, playerTexture, input, windowIn);
	player->init();
}

void Game::update(float dt)
{//update game logic
	physicsWorld->Step(0.06f, 6, 2);
	player->update(dt);
	gameFloor->update(dt);
	sendPackets();
}

void Game::render()
{//render stuff
	window->draw(floor);
	gameFloor->render();
	player->render();
}

void Game::deload()
{
}

GameState Game::needsChange()
{
	return GameState::NoChange;
}

void Game::sendPackets()
{//send packet of current position and state of the controlling player to the server
	playerMoveMessage packetOut;
	sf::Packet packet;

	packetOut.stateMessage = static_cast<int>(player->getState());
	packetOut.xPos = player->getPhysicsBody()->GetPosition().x;
	packetOut.xPos = player->getPhysicsBody()->GetPosition().x;
	//shove data into packet
	//packet << packetOut;
	if (socket->send(packet, serverIp, 7777) != sf::Socket::Done)
	{
		//error here
	}
}
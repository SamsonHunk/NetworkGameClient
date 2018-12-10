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

	unsigned short serverPort = 7777;
	unsigned short clientPort = 5410;

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
	
	serverIp = sf::IpAddress("127.0.0.1");
	connectionMessage packetOut;
	packetOut.clientIp = sf::IpAddress::LocalHost.toString();
	packetOut.port = clientPort;
	packetOut.messageType = 1;

	

	socketHandle.add(*socket);
	
	socket->setBlocking(true);
	sf::Packet outPacket;
	outPacket << packetOut.messageType << packetOut.clientIp << packetOut.port;
	if (socket->send(outPacket, serverIp, 7777) != sf::Socket::Done) //connect to server
	{

	}

	sf::Packet connectionPacket;
	playerMoveMessage connectionConfirm;
	sf::IpAddress anyIp = sf::IpAddress::Any;
	sf::IpAddress serverIN;
	unsigned short PortIn;
	//wait for a message for the server telling us we are in the game
	if (socket->receive(connectionPacket, serverIN, PortIn) != sf::Socket::Done)
	{
		//error connecting to server
		int debug = 0;
	}
	else
	{
		connectionPacket >> connectionConfirm.messageType >> connectionConfirm.stateMessage >> connectionConfirm.xPos >> connectionConfirm.yPos >> connectionConfirm.playerNum;
	}

	gameFloor = new Floor(physicsWorld, floorTexture, input, windowIn);
	gameFloor->init(0,0);

	player = new Player(physicsWorld, playerTexture, input, windowIn);
	player->init(connectionConfirm.xPos, connectionConfirm.yPos);
	playerNum = connectionConfirm.playerNum;

	player2 = new Player2(physicsWorld, playerTexture, input, windowIn);
	player2->init(600, 0);

	socket->setBlocking(false);
}

void Game::update(float dt)
{//update game logic
	physicsWorld->Step(0.06f, 6, 2);
	player->update(dt);
	pingReciever();
	applyPing();
	player2->update(dt);
	gameFloor->update(dt);
	sendPackets();
}

void Game::render()
{//render stuff
	window->draw(floor);
	gameFloor->render();
	player->render();
	player2->render();
}

void Game::deload()
{
	needsDone = true;
}

GameState Game::needsChange()
{
	return GameState::NoChange;
}

void Game::sendPackets()
{//send packet of current position and state of the controlling player to the server
	playerMoveMessage packetOut;

	packetOut.stateMessage = static_cast<int>(player->getState());
	packetOut.xPos = player->getPhysicsBody()->GetPosition().x;
	packetOut.yPos = player->getPhysicsBody()->GetPosition().y;
	packetOut.playerNum = playerNum;
	//shove data into packet
	movePacketOut << packetOut.messageType << packetOut.stateMessage << packetOut.xPos << packetOut.yPos << packetOut.playerNum;
	if (socket->send(movePacketOut, serverIp, 7777) != sf::Socket::Done)
	{
		//error here
	}
	else
	{
		//when the socket is done, clear the packet
		movePacketOut.clear();
	}
}

void Game::pingReciever()
{//function to wait for the next server ping this will wait on it's own thread until it recieves input
	


		if (socket->receive(pingPacket, ipReciept, portReceipt) != sf::Socket::Done)
		{
			//
			int debug = 0;
		}
		else
		{//grab the message
			int messageType;
			pingPacket >> messageType;
			switch (messageType)
			{
			case 3:
				//grab packet and store it into the message stack
				pingPacket >> packetIn.xPos1 >> packetIn.yPos1 >> packetIn.player1State >> packetIn.xPos2 >> packetIn.yPos2 >> packetIn.player2State;
				latestPing = packetIn;
				isNew = true;
				pingPacket.clear();
				break;

			default:
				break;
			}
		}
	}


void Game::applyPing()
{
	if (isNew)
	{
		
		switch (playerNum)
		{
		case 1:
			player2->input.newState = static_cast<PlayerStates>(latestPing.player2State);
			player2->input.pos[0] = latestPing.xPos2;
			player2->input.pos[1] = latestPing.yPos2;
			player2->input.dir = true;
			player2->input.inAir = false;
			player2->input.newInfo = true;
			break;
		case 2:
			player2->input.newState = static_cast<PlayerStates>(latestPing.player1State);
			player2->input.pos[0] = latestPing.xPos1;
			player2->input.pos[1] = latestPing.yPos1;
			player2->input.dir = true;
			player2->input.inAir = false;
			player2->input.newInfo = true;
			break;
		default:
			break;
		}
		isNew = false;
	}
}
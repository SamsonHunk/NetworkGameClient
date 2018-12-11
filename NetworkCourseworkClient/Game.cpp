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
	unsigned short clientPort = 5400;

	//initialise gameworld gravity
	physicsWorld = new b2World(b2Vec2(0, .5));
	
	//setup stage floor
	floor.setPosition(200, 400);
	floor.setFillColor(sf::Color::Red);
	floor.setSize(sf::Vector2f(400, 50));
	playerTexture = new sf::Texture();
	floorTexture = new sf::Texture();
	bulletTexture = new sf::Texture();

	playerTexture->loadFromFile("image/player.png");
	floorTexture->loadFromFile("image/floor.png");
	bulletTexture->loadFromFile("image/bullet.png");

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

	//initialise bullets lists
	for (int it = 0; it < maxBullets; it++)
	{
		playerBullets[it] = new Bullet(physicsWorld, bulletTexture, input, windowIn);
		playerBullets[it]->init(0, 0);
		enemyBullets[it] = new Bullet(physicsWorld, bulletTexture, input, windowIn);
		playerBullets[it]->init(0, 0);
	}

	socket->setBlocking(false);
}

void Game::update(float dt)
{//update game logic
	physicsWorld->Step(0.06f, 6, 2);
	player->update(dt);
	bulletShoot();
	pingReciever();
	applyPing();
	player2->update(dt);
	gameFloor->update(dt);
	collisionDetect();
	sendPackets();
}

void Game::render()
{//render stuff
	window->draw(floor);
	gameFloor->render();
	player->render();
	player2->render();
	for (int it = 0; it < maxBullets; it++)
	{//only render bullets currently being used
		if (playerBullets[it]->awake)
		{
			playerBullets[it]->render();
		}

		if (enemyBullets[it]->awake)
		{
			enemyBullets[it]->render();
		}
	}
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

void Game::collisionDetect()
{
	//get the list of current collisions in the physics world
	b2Contact* contact = physicsWorld->GetContactList();
	int contactCount = physicsWorld->GetContactCount();

	//iterate through the list and do collision response accordingly
	for (int contactIt = 0; contactIt < contactCount; contactIt++)
	{
		if (contact->IsTouching())
		{
			//grab colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			//grab their gameobjects
			GameObj* objA = (GameObj*)bodyA->GetUserData();
			GameObj* objB = (GameObj*)bodyB->GetUserData();

			//object pointers to detect what is colliding with what
			Player* playerPointer = NULL;
			Floor* floorPointer = NULL;
			Player2* player2Pointer = NULL;
			Bullet* bulletPointer = NULL;

			if (objA)
			{
				switch (objA->getType())
				{
				case ObjectType::PLAYER:
					//if the player is colliding activate the pointer
					playerPointer = (Player*)bodyA->GetUserData();
					break;
				case ObjectType::FLOOR:
					floorPointer = (Floor*)bodyA->GetUserData();
					break;
				case ObjectType::PLAYER2:
					player2Pointer = (Player2*)bodyA->GetUserData();
				case ObjectType::BULLET:
					bulletPointer = (Bullet*)bodyA->GetUserData();
					break;
				}
			}

			if (objB)
			{
				switch (objB->getType())
				{
				case ObjectType::PLAYER:
					//if the player is colliding activate the pointer
					playerPointer = (Player*)bodyB->GetUserData();
					break;
				case ObjectType::FLOOR:
					floorPointer = (Floor*)bodyB->GetUserData();
					break;
				case ObjectType::PLAYER2:
					player2Pointer = (Player2*)bodyB->GetUserData();
					break;
				case ObjectType::BULLET:
					bulletPointer = (Bullet*)bodyB->GetUserData();
					break;
				}
			}

			if (playerPointer && floorPointer)
			{//if the player is currently standing on the ground, allow him to jump
				playerPointer->inAir = false;
			}
			else if (player2Pointer && floorPointer)
			{//same with the other player
				player2Pointer->inAir = false;
			}
			else if (bulletPointer && player2Pointer)
			{
				bulletPointer->deactivate();
			}
		}
	}
}

void Game::bulletShoot()
{
	if (player->getShooting())
	{// if the player is currently shooting, check if we can add another bullet to the pile
		bool found = false;
		int it = 0;
		while (!(found || it == maxBullets))
		{//if there is an empty slot on the bullet array shoot out a new bullet
			if (!playerBullets[it]->awake)
			{
				//shoot left or right depending which way the player is moving
				if (player->getDir())
				{
					playerBullets[it]->activate(player->getPhysicsBody()->GetPosition().x + 50, player->getPhysicsBody()->GetPosition().y, true);
				}
				else
				{
					playerBullets[it]->activate(player->getPhysicsBody()->GetPosition().x - 50, player->getPhysicsBody()->GetPosition().y, false);
				}
				found = true;
			}
			it++;
		}
	}

	//update the bullets
	for (int it = 0; it < 4; it++)
	{
		if (playerBullets[it]->awake)
		{
			playerBullets[it]->update(1);
		}

		if (enemyBullets[it]->awake)
		{
			enemyBullets[it]->update(1);
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
			player2->input.newInfo = true;
			break;
		case 2:
			player2->input.newState = static_cast<PlayerStates>(latestPing.player1State);
			player2->input.pos[0] = latestPing.xPos1;
			player2->input.pos[1] = latestPing.yPos1;
			player2->input.dir = true;
			player2->input.newInfo = true;
			break;
		default:
			break;
		}
		isNew = false;
	}
}
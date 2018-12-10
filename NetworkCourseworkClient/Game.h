#pragma once
#include "State.h"
#include "Player.h"
#include "Player2.h"
#include "Floor.h"
#include <list>
#include <mutex>

//state for ingame
class Game: public State
{
public:
	Game();
	~Game();

	void init(sf::RenderWindow* windowIn, Input* in, sf::UdpSocket* socketIn);
	void update(float dt);
	void render();
	void deload();
	GameState needsChange();


private:
	sf::RectangleShape floor;
	sf::IpAddress serverIp;
	b2World* physicsWorld;
	Player* player;
	Player2* player2;
	Floor* gameFloor;
	sf::Texture* playerTexture;
	sf::Texture* floorTexture;
	sf::SocketSelector socketHandle;

	sf::Packet pingPacket;
	sf::Packet movePacketOut;

	sf::IpAddress ipReciept;
	unsigned short portReceipt;
	serverPositionPing packetIn;

	int playerNum;
	void sendPackets();
	void applyPing();
	void pingReciever();
	void collisionDetect();
	bool needsDone = false;

private:
	//message containers
	serverPositionPing latestPing;
	bool isNew = false;
};

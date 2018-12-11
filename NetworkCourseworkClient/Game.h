#pragma once
#include "State.h"
#include "Player.h"
#include "Player2.h"
#include "Floor.h"
#include "Bullet.h"
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
	Bullet* playerBullets[4];
	Bullet* enemyBullets[4];
	sf::Texture* playerTexture;
	sf::Texture* floorTexture;
	sf::Texture* bulletTexture;
	sf::SocketSelector socketHandle;

	sf::Packet pingPacket;
	sf::Packet movePacketOut;
	sf::Packet bulletPackets[4];

	sf::IpAddress ipReciept;
	unsigned short portReceipt;
	serverPositionPing packetIn;

	int playerNum;
	void sendPackets();
	void applyPing();
	void pingReciever();
	void collisionDetect();
	void bulletShoot();
	bool needsDone = false;

	
private:
	//message containers
	serverPositionPing latestPing;
	serverBulletPing latestBullet;
	bool isNew = false;
};

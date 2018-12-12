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

	void init(sf::RenderWindow* windowIn, Input* in, sf::UdpSocket* socketIn, std::string serverIpIn, std::string clientIn);
	void update(float dt);
	void render();
	void deload();
	GameState needsChange();
	

private:
	sf::IpAddress ipOut = sf::IpAddress::getLocalAddress();
	sf::RectangleShape floor;
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
	serverBulletPing bulletPacketUnpack(sf::Packet *in);
	bool needsDone = false;

	std::string serverIp;
	std::string clientIPAddress;
private:
	//message containers
	serverPositionPing latestPing;
	serverBulletPing latestBullet;
	bool isNew = false;
	bool newBullet = false;
};

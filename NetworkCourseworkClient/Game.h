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
	void pingReciever();


private:
	sf::RectangleShape floor;
	sf::IpAddress serverIp;
	b2World* physicsWorld;
	Player* player;
	Player2* player2;
	Floor* gameFloor;
	sf::Texture* playerTexture;
	sf::Texture* floorTexture;

	std::thread* pingGrabThread;

	int playerNum;
	void sendPackets();
	void applyPing();
	bool needsDone = false;

private:
	//message containers
	std::mutex messageLock;
	serverPositionPing latestPing;
	bool isNew = false;
};

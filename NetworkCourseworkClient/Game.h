#pragma once
#include "State.h"
#include "Player.h"
#include "Floor.h"
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
	b2World* physicsWorld;
	Player* player;
	Floor* gameFloor;
	sf::Texture* playerTexture;
	sf::Texture* floorTexture;
};

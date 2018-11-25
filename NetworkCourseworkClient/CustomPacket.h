#pragma once
#include "Global.h"
#include <SFML/Network/Packet.hpp>

class CustomSocket: public sf::Packet
{//custom extension to sf::Packet to allow me to use my own custom structs
public:
	using sf::Packet::Packet;

	CustomSocket& operator <<(const playerMoveMessage structIn);
	CustomSocket& operator >>(playerMoveMessage structIn);

	CustomSocket& operator <<(const connectionMessage structIn);
	CustomSocket& operator >>(connectionMessage structIn);
};

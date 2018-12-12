#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <Box2D.h>
#include "State.h"
#include "Input.h"
#include "Global.h"
#include "Game.h"
#include <iostream>

// The IP address of the server


int main()
{
	std::string serverIp;
	std::string clientIp;
	Input input; //Input manager for keyboard
	sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Snap Brother"); //initialise game window
	float deltaTime; //delta time for accurate movement between frames
	sf::Clock clock; //clock to time deltatime
	sf::UdpSocket socket; //UDP socket for communicating with the server

	unsigned short port = 5400;
	int playerNUM;
	std::cout << "Player 1 or player 2? (1 or 2)" << std::endl;
	std::cin >> playerNUM;

	if (playerNUM == 1)
	{
		port = 5410;
	}
 
	std::cout << "Localhost or LAN? (1 or 2)" << std::endl;
	std::cin >> playerNUM;

	switch (playerNUM)
	{
	case 1:
		if (socket.bind(port, "127.0.0.1") != socket.Done)
		{//if server connect fails
			return 1;
		}
		else
		{
			clientIp = sf::IpAddress::getLocalAddress().LocalHost.toString();
			std::cout << "Client ip: " << clientIp << " " << port << std::endl;
			serverIp = sf::IpAddress::LocalHost.toString();
		}
		break;
	case 2:
		if (socket.bind(port, sf::IpAddress::getLocalAddress()) != socket.Done)
		{//if server connect fails
			return 1;
		}
		else
		{
			std::string input;
			clientIp = sf::IpAddress::getLocalAddress().toString();
			std::cout << "Client ip: " << clientIp << " " << port << std::endl;
			std::cout << "Server ip: " << std::endl;
			std::cin >> serverIp;
			std::cout << "Connecting to " << serverIp << " on port: " << serverPort << std::endl;
		}
		break;
	default:
		break;
	}
	
	State* currentState = nullptr; //pointer for the current game state

	currentState = new Game;
	currentState->init(&window, &input, &socket, serverIp, clientIp);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0,
					event.size.width, event.size.height)));
				break;
			case sf::Event::KeyPressed:
				input.KeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.KeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				input.updateMouseCoords(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				input.mouseDown(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				input.mouseUp(event.mouseButton.button);
				break;
			default:
				// don't handle other events
				break;
			}
		}
		deltaTime = clock.restart().asMilliseconds();
		//calculate delta time
		currentState->update(deltaTime);

		window.clear();
		currentState->render();
		window.display();
		//run game logic

		//check if we need to check gamestate
		if (currentState->needsChange() != GameState::NoChange)
		{
			GameState nextGameState = currentState->needsChange();
			//grab next gamestate
			currentState->deload();
			//unload the current state
			switch (nextGameState)
			{//run init function and load the next game state
			case GameState::Menu:
				break;
			case GameState::GameENUM:
				break;
			case GameState::NoChange:
				break;
			}
		}
	}

	return 0;
}
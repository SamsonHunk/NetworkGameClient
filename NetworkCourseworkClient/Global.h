#ifndef GLOBALVARS
#define GLOBALVARS
extern enum class PlayerStates { movingLeft, movingRight, stationary, movingUp, movingDown };
extern enum class ObjectType {FLOOR, PLAYER, BULLET, PLAYER2};

extern struct playerMoveMessage {
	int messageType = 2;
	int stateMessage;
	float xPos;
	float yPos;
	int playerNum;
	bool dir;
	float yVel;
};

extern struct  connectionMessage
{
	int messageType = 1;
	std::string clientIp;
	unsigned short port;
};

extern struct serverPositionPing
{
	int messageType = 3;
	float xPos1;
	float yPos1;
	int player1State;
	float xPos2;
	float yPos2;
	int player2State;
	float yVel1;
	float yVel2;
};

extern struct playerShootPing
{
	int messageType = 5;
	float posx;
	float posy;
	bool dir;
	int bulletNum;
	int playerNum;
};

extern struct serverBulletPing
{//maximum bullets in the scene will be 8, 4 for each player
	int messageType = 4;
	float posx[4];
	float posy[4];
	bool awake[4];
	bool dir[4];
};



	extern enum  GameState { Menu, GameENUM, NoChange }; //enumerator for the current game state
	namespace GLOBALVARS {
		//enum for current playerstate

		extern int leftControl = sf::Keyboard::A;
		extern int rightControl = sf::Keyboard::D;
		extern int jumpControl = sf::Keyboard::W;
		extern int shootControl = sf::Keyboard::Space;
		extern int crouchControl = sf::Keyboard::S; //Didn't get to implement, ran out of time ;-;
		extern int lagToggleControl = sf::Keyboard::L;
		extern int maxBullets = 4;

		extern unsigned short serverPort = 7777;
	}
	
#endif // !GLOBALVARS
//file to store project wide data containers
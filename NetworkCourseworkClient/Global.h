#ifndef GLOBALVARS
#define GLOBALVARS
namespace GLOBALVARS
{
	extern enum class GameState { Menu, Game, NoChange }; //enumerator for the current game state
	extern 	enum class PlayerStates { movingLeft, movingRight, stationary, movingUp, movingDown };
	//enum for current playerstate

	extern int leftControl = sf::Keyboard::A;
	extern int rightControl = sf::Keyboard::D;

	extern struct playerMoveMessage {
		PlayerStates stateMessage;
		b2Vec2 position;
	};
}
#endif // !GLOBALVARS
//file to store project wide data containers
#ifndef GLOBALVARS
#define GLOBALVARS
namespace GLOBALVARS
{
	extern enum class GameState { Menu, Game, NoChange }; //enumerator for the current game state

	extern int leftControl = sf::Keyboard::W;
	extern int rightControl = sf::Keyboard::A;
}
#endif // !GLOBALVARS
//file to store project wide data containers
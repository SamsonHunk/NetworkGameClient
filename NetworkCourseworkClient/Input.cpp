#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

void Input::KeyDown(int in)
{
	keys[in] = true;
}

void Input::KeyUp(int in)
{
	keys[in] = false;
}

bool Input::getKey(int in)
{
	return keys[in];
}

void Input::updateMouseCoords(int x, int y)
{
	coords[0] = x; //coords 0 is x
	coords[1] = y; //coords 1 is y
}

int Input::getCoord(int in)
{
	return coords[in];
}

bool Input::getKeys()
{
	return &keys;
}

void Input::mouseDown(int in)
{
	mouse[in] = true;
}

void Input::mouseUp(int in)
{
	mouse[in] = false;
}

bool Input::getMouseButt(int in)
{
	return mouse[in];
}
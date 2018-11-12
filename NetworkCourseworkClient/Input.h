#pragma once
//input manager stolen from my year 1 games programming coursework
class Input
{
public:
	Input();
	~Input();
	void KeyDown(int in);
	void KeyUp(int in);
	bool getKey(int in);
	void updateMouseCoords(int x, int y);
	int getCoord(int in);
	bool getKeys();
	void mouseUp(int in);
	void mouseDown(int in);
	bool getMouseButt(int in);

private:
	bool keys[256] = { false };
	int coords[2];
	bool mouse[10] = { false };
};


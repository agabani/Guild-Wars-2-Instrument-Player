#pragma once
#include "controller.h"
class OnScreen :
	public Controller
{
public:
	OnScreen(void);
	~OnScreen(void);

	int init();
	int pressNumber(int number);

private:
	int moveMouse(int x, int y);
	int leftClick();

	int trainMouse();
	int saveTrain();
	int loadTrain();

private:
	POINT buttonMap[10];
	HWND keyboard, guildwars2;
};


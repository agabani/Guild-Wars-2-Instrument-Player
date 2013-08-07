#include "stdafx.h"
#include "OnScreen.h"


OnScreen::OnScreen(void)
{
	// Obtain window handles
	keyboard = FindWindowA(NULL, "On-Screen Keyboard");
//	guildwars2 = FindWindowA(NULL, "Guild Wars 2");
	guildwars2 = FindWindowA(NULL, "Untitled - Notepad");

	// Check if On-Screen keyboard is active
	RECT keyboardlocation;
	GetWindowRect(keyboard, &keyboardlocation);

	if (keyboardlocation.left < 0 || keyboardlocation.top < 0)
	{
		std::cout << "Cannot find On-Screen Keyboard\n\tPress Enter/Return key to exit." << std::endl;
		std::cin.ignore(1000, '\n');
		std::cin.clear();
		exit(1);
	}

	// Load mouse training
	if (loadTrain())
	{
		trainMouse();
		saveTrain();
	}
}


OnScreen::~OnScreen(void)
{
}


int OnScreen::init()
{
	return 0;
}


int OnScreen::pressNumber(int number)
{
	ShowWindow(guildwars2, SW_RESTORE);
    SetForegroundWindow(guildwars2);
    SetFocus(guildwars2);

	keyboard = FindWindowA(NULL, "On-Screen Keyboard");
	RECT keyboardlocation;
	GetWindowRect(keyboard, &keyboardlocation);

	moveMouse(keyboardlocation.left + buttonMap[number].x, keyboardlocation.top + buttonMap[number].y);
	leftClick ();
	return 0;
}


int OnScreen::moveMouse(int x, int y)
{
	double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
	double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
	double fx = x*(65535.0f/fScreenWidth);
	double fy = y*(65535.0f/fScreenHeight);
	INPUT  Input={0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE|MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (LONG)fx;
	Input.mi.dy = (LONG)fy;
	::SendInput(1,&Input,sizeof(INPUT));

	return 0;
}


int OnScreen::leftClick()
{
	INPUT Input={0};
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	::SendInput(1,&Input,sizeof(INPUT));

	::ZeroMemory(&Input,sizeof(INPUT));
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	::SendInput(1,&Input,sizeof(INPUT));

	return 0;
}

// todo: change training program to GUI
int OnScreen::trainMouse()
{
	RECT keyboardlocation;
	
	std::cout << "Mouse training has not been found. Beginning mouse training program.\n\n";
	std::cout << "Instructions:\n\tWhilst this program is your ACTIVE window,\n"
		<< "\thover your mouse over the number specified\n\tand press RETURN (do not left click)\n\n";

	for (int numkey = 0; numkey <= 9; numkey++)
	{
		std::cout << "Hover over number: " << numkey;
		
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.ignore(1000, '\n');
		std::cin.clear();

		GetCursorPos(&buttonMap[numkey]);
		GetWindowRect(keyboard, &keyboardlocation);

		buttonMap[numkey].x -= keyboardlocation.left;
		buttonMap[numkey].y -= keyboardlocation.top;
	}

	return 0;
}

// todo: change training save to Qt
int OnScreen::saveTrain()
{
	std::fstream train;
	train.open ("controller/onscreen/train.txt", std::fstream::out | std::fstream::trunc);
	
	for (int i = 0; i <= 9; i++)
	{
		train << (int)buttonMap[i].x << " " << (int)buttonMap[i].y << " ";
	}

	train.close();

	std::cout << "Training complete...\n\n";

	return 0;
}

// todo: change load training to Qt
int OnScreen::loadTrain()
{
	std::fstream train;
	train.open ("controller/onscreen/train.txt", std::fstream::in);

	if (!train.good())
	{
		train.close();
		return 1;
	}

	for (int i = 0; i <= 9; i++)
	{
		train >> buttonMap[i].x >> buttonMap[i].y;
	}

	train.close();
	return 0;
}

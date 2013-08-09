#include "stdafx.h"
#include "Instrument.h"

Instrument::Instrument(void)
	: _controller(NULL), _octave(1)
{	
}

Instrument::~Instrument(void)
{
	if (_controller != NULL)
	{
		delete _controller;
		_controller = NULL;
	}
}

int Instrument::loadOnScreen(ControllerType value)
{
	if (_controller != NULL)
	{
		delete _controller;
		_controller = NULL;
	}
	
	switch (value)
	{
	case Instrument::ONSCREEN:
		_controller = new OnScreen;
		break;
	case Instrument::VKEYBOARD:
//		_controller = new VirtualKeyboard; // todo, impliment a virtual keyboard class
		break;
	default:
		break;
	}

	return 0;
}

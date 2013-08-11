#include "stdafx.h"
#include "Flute.h"

Flute::Flute(void)
{
	_note = -1;
	notePlaying = false;
	loadController(ONSCREEN);
}

Flute::~Flute(void)
{
}

int Flute::init()
{
	return 0;
}

int Flute::playNote(int value)
{
	_controller->pressNumber(value);
	notePlaying = true;

	_note = value;
	return 0;
}

int Flute::stopNote()
{
	if (notePlaying == false) {
		return 0;
	}

	_controller->pressNumber(0);
	notePlaying = false;
	return 0;
}

int Flute::switchOctave(int octave)
{
	if (_octave == octave) {
		return 0;
	}
	
	_controller->pressNumber(9);
	_octave = octave;
	return 0;
}

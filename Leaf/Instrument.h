#pragma once
#include "OnScreen.h"

class Instrument
{
public:
	Instrument(void);
	~Instrument(void);

public:
	virtual int init() = 0;
	int loadOnScreen();

public:
	virtual int playNote(int note) = 0;
	virtual int stopNote() = 0;
	virtual int switchOctave(int octave) = 0;

protected:
	Controller *controller;
	int octave;
	int note;
	
};

#pragma once
#include "instrument.h"
class Bell :
	public Instrument
{
public:
	Bell(void);
	~Bell(void);

public:
	int init();
	int playNote(int note);
	int stopNote();
	int switchOctave(int octave);
};


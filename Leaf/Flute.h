#pragma once
#include "instrument.h"
class Flute :
	public Instrument
{
public:
	Flute(void);
	~Flute(void);

public:
	int init();
	int playNote(int note);
	int stopNote();
	int switchOctave(int octave);

private:
	bool notePlaying;
};


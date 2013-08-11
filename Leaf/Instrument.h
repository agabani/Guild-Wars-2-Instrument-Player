#ifndef __INSTRUMENT_H__
#define __INSTRUMENT_H__

#include "OnScreen.h"

class Instrument
{
public:
	Instrument(void);
	~Instrument(void);

public:
	enum ControllerType {
		ONSCREEN,
		VKEYBOARD
	};

	virtual int init() = 0;
	int loadController(ControllerType);

public:
	virtual int playNote(int note) = 0;
	virtual int stopNote() = 0;
	virtual int switchOctave(int octave) = 0;

protected:
	Controller *_controller;
	int _octave;
	int _note;
	
};

#endif // __INSTRUMENT_H__

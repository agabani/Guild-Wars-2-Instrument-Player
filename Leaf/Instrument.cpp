#include "stdafx.h"
#include "Instrument.h"


Instrument::Instrument(void)
{
	loadOnScreen();
	octave = 1;

	loadOnScreen();
}


Instrument::~Instrument(void)
{
}


int Instrument::loadOnScreen()
{
	controller = new OnScreen;
//	qDebug() << "loaded controller\n";
	return 0;
}

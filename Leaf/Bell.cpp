#include "stdafx.h"
#include "Bell.h"


Bell::Bell(void)
{
}


Bell::~Bell(void)
{
}


int Bell::init()
{
	return 0;
}


int Bell::playNote(int note)
{
	std::cout << "Bell:" << note << std::endl;
	return 0;
}


int Bell::stopNote()
{
	return 0;
}


int Bell::switchOctave(int octave)
{
	return 0;
}
#include "stdafx.h"
#include "Flute.h"


Flute::Flute(void)
{
	note = -1;
	notePlaying = false;
}


Flute::~Flute(void)
{
}


int Flute::init()
{
	return 0;
}


int Flute::playNote(int _note)
{
	if (note == _note)
	{
		stopNote();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	controller->pressNumber(_note);
	notePlaying = true;

	note = _note;
	return 0;
}

int Flute::stopNote()
{
	if (notePlaying == false)
		return 0;

	controller->pressNumber(note);
	notePlaying = false;
	return 0;
}

int Flute::switchOctave(int _octave)
{
	blocker.lock();
	if (_octave != octave) {
		controller->pressNumber(9);
		octave = _octave;
	}

	std::thread t(&Flute::startTimeout,this);
	t.detach();
	
	blocker.unlock();

	return 0;
}


void Flute::startTimeout()
{
	std::lock_guard<std::mutex> m(blocker);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}


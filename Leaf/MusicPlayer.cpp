#include "stdafx.h"
#include "MusicPlayer.h"


MusicPlayer::MusicPlayer(void)
{
}


MusicPlayer::~MusicPlayer(void)
{
}


int MusicPlayer::loadBell()
{
	instrument = new Bell;
	instrumentName = "Bell"; // User readable
	return 0;
}


int MusicPlayer::loadFlute()
{
	instrument = new Flute;
	instrumentName = "Flute"; // User readable
	return 0;
}

int MusicPlayer::loadHorn()
{
	instrument = new Horn;
	instrumentName = "Horn"; // User readable
	return 0;
}


int MusicPlayer::loadMusicSheet(std::vector <char> object)
{
	musicSheet = object;
	return 0;
}


int MusicPlayer::playSong()
{
	int beat = 60 * 1000 / tempo;
	int octave = 1;

	for (unsigned int i = 0; i < musicSheet.size(); i++)
	{	
		switch (musicSheet.at(i))
		{
		case 0:

			for (int forward = 1; i + forward < musicSheet.size(); forward++)
			{
				switch (musicSheet.at(i + forward))
				{
				case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9': case '0':
					forward = musicSheet.size();
					break;
				case 'w': case 'h': case 'q': case 's': case 't': case 'S':
					instrument->stopNote();
					forward = musicSheet.size();
					break;
				default:
					break;
				}
			}

			break;
		case '1': instrument->playNote(1); break;
		case '2': instrument->playNote(2); break;
		case '3': instrument->playNote(3); break;
		case '4': instrument->playNote(4); break;
		case '5': instrument->playNote(5); break;
		case '6': instrument->playNote(6); break;
		case '7': instrument->playNote(7); break;
		case '8': instrument->playNote(8); break;
		case '9': instrument->playNote(9); break;
		case '0': instrument->playNote(0); break;

		case 'w':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat*4*measure)));
			break;
		case 'h':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat*2*measure)));
			break;
		case 'q':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat)));
			break;
		case 'e':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat/2)));
			break;
		case 's':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat/4)));
			break;
		case 't':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat/8)));
			break;
		case 'S':
			std::this_thread::sleep_for(std::chrono::milliseconds(int(beat/16)));
			break;

		case 'L':
			if (octave != 1)
			{
				instrument->switchOctave(1);
				octave = 1;
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			break;
		case 'M':
			if (octave != 2)
			{
				instrument->switchOctave(2);
				octave = 2;
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			break;
		case 'H':
			if (octave != 3)
			{
				instrument->switchOctave(3);
				octave = 3;
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}
			break;

		default:
			break;
		}
	}

	// Reset octave to low for curtosy...
	if (octave != 1)
	{
		instrument->switchOctave(1);
		octave = 1;
	}

	return 0;
}


int MusicPlayer::setTempo(int value)
{
	tempo = value;
	return 0;
}


int MusicPlayer::setMeasure(float value)
{
	measure = value;
	return 0;
}


int MusicPlayer::getTempo()
{
	return tempo;
}


float MusicPlayer::getMeasure()
{
	return measure;
}


std::string MusicPlayer::getInstrumentName()
{
	return instrumentName;
}

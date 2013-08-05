#include "stdafx.h"
#include "FileManager.h"

template <class T>
T getValue (std::string &text, std::string term)
{
	T value;

	std::stringstream ss;
	size_t startLoc, endLoc;

	startLoc = text.find(term);

	if (startLoc == std::string::npos) {
		return 0;
	}

	startLoc += term.length() + 1;
	endLoc = text.find('"', startLoc);

	ss << text.substr(startLoc, endLoc-startLoc);
	ss >> value;

	return value;
}


int getMusicSheet (std::string &text, std::vector <char> &sheet)
{
	std::string term = "[SHEET START]";

	size_t startLoc = text.find(term);

	if (startLoc == std::string::npos)
		return 1;

	startLoc += term.length();

	term = "[SHEET END]";
	size_t endLoc = text.find(term);

	if (endLoc == std::string::npos)
		return 2;

	// Process sheet
	for (unsigned int index = startLoc; index < endLoc; index++)
	{
		switch (text.at(index))
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':

		case 'w':
		case 'h':
		case 'q':
		case 'e':
		case 's':
		case 't':
		case 'S':

		case 'L':
		case 'M':
		case 'H':

			sheet.push_back(text.at(index));
			break;

		case ' ':
		case '\n':
		case '[':
		case ']':

			sheet.push_back(0);
			break;

		default:
			break;
		}
	}

	return 0;
}


int loadSong(std::string path, MusicPlayer *object)
{
	// Save file in buffer
	std::fstream musicFile;
	musicFile.open(path, std::ios_base::in | std::ios_base::binary);

	if (!musicFile.good()) {
		return 1;
	}

	musicFile.seekg(0, musicFile.end);
	int fileSize = (int)musicFile.tellg();
	musicFile.seekg(0, musicFile.beg);

	std::string fileContent;
	fileContent.resize(fileSize);

	musicFile.read(&fileContent[0], fileSize);

	musicFile.close();

	// Pulling song data
	int tempo = getValue <int> (fileContent,"Tempo=");
	float measure = getValue <float> (fileContent, "Measure=");
	std::string instrument = getValue <std::string> (fileContent, "Instrument=");

	if (!tempo || !measure || !instrument.length()) {
		return 2;
	}

	// Pull music sheet
	std::vector <char> sheet;
	if (getMusicSheet(fileContent, sheet)) {
		return 3;
	}

	// Create object
	if (instrument == "bell")
		object->loadBell();
	else if (instrument == "flute")
		object->loadFlute();
	else if (instrument == "Horn")
		object->loadHorn();
	else return 4;

	object->setTempo(tempo);
	object->setMeasure(measure);

	object->loadMusicSheet(sheet);

	return 0;
}


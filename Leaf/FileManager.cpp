#include "stdafx.h"
#include "FileManager.h"


QString getValue (QString& text, QString term)
{
	int start = text.indexOf(term,0);

	if (start == -1) {
		return 0;
	}

	start += term.length()+1;
	int end = text.indexOf('"',start+1);

	return text.mid(start, end-start);
}
/*
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
*/
int getMusicSheet (QString &text, std::vector <char> &sheet)
{
	QString term = "[SHEET START]";
	int start = text.indexOf(term,0);
	if (start == -1) {
		return 1;
	}
	start += term.length();

	term = "[SHEET END]";
	int end = text.indexOf(term,0);
	if (end == -1) {
		return 2;
	}

	// Process sheet
	for (unsigned int index = start; index < end; index++)
	{
		switch (text.at(index).toLatin1())
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

			sheet.push_back(text.at(index).toLatin1());
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


int loadSong(QString path, MusicPlayer *object)
{
	// Pull file contents
	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
	}

	QTextStream in(&file);

	QString line = in.readAll();
	std::string fileContent = line.toLocal8Bit().constData();

	// Pulling song data
	int tempo = getValue(line,"Tempo=").toInt();
	float measure = getValue(line, "Measure=").toFloat();
	QString instrument = getValue(line, "Instrument=");

	if (!tempo || !measure || !instrument.length()) {
		return 2;
	}

	// Pull music sheet
	std::vector <char> sheet;
	if (getMusicSheet(line, sheet)) {
		return 3;
	}

	// Create object
	if (instrument == "bell")
		object->loadBell();
	else if (instrument == "flute")
		object->loadFlute();
	else if (instrument == "horn")
		object->loadHorn();
	else return 4;

	object->setTempo(tempo);
	object->setMeasure(measure);
	object->loadMusicSheet(sheet);

	return 0;
}


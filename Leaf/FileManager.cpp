#include "stdafx.h"
#include "FileManager.h"

int FileManager::loadSong(QString path, MusicPlayer &object)
{
	MusicPlayer::MusicSheet musicSheet;

	// Pull file contents
	QFile file(path);
	if(!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(0, "Error", file.errorString());
	}

	QTextStream in(&file);

	QString line = in.readAll();
	std::string fileContent = line.toLocal8Bit().constData();

	// Pulling song data
	musicSheet.tempo = getValue(line,"Tempo=").toInt();
	musicSheet.timeSignature = getValue(line, "Measure=").toFloat();
	QString instrument = getValue(line, "Instrument=");

	if (!musicSheet.tempo || !musicSheet.timeSignature || !instrument.length()) {
		return 2;
	}

	// Pull music sheet
	if (getMusicSheet(line, musicSheet.notes)) {
		return 3;
	}
 
	object.setMusicSheet(musicSheet);
	

	// Create object
	if (instrument == "bell") {
		object.setInstrument(MusicPlayer::InstrumentType::BELL);
	}
	else if (instrument == "flute") {
		object.setInstrument(MusicPlayer::InstrumentType::FLUTE);
	}
	else if (instrument == "horn") {
		object.setInstrument(MusicPlayer::InstrumentType::HORN);
	}
	else return 4;

	return 0;
}

QString FileManager::getValue (QString& text, QString term)
{
	int start = text.indexOf(term,0);

	if (start == -1) {
		return 0;
	}

	start += term.length()+1;
	int end = text.indexOf('"',start+1);

	return text.mid(start, end-start);
}

int FileManager::getMusicSheet (QString &text, std::vector <char> &sheet)
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
		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case 'w': case 'h':
		case 'q': case 'e': case 's': case 't': case 'S':
		case 'L': case 'M': case 'H':
			sheet.push_back(text.at(index).toLatin1());
			break;

		case ' ': case '\n': case '[': case ']':
			sheet.push_back(0);
			break;

		default:
			break;
		}
	}

	return 0;
}

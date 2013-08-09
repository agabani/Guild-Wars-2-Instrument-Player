#include "stdafx.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(void)
	: _timer (NULL), _tickRate(25), _isPlaying(false), _instrument(NULL)
{
}

MusicPlayer::~MusicPlayer(void)
{
	if (_instrument != NULL) {
		delete _timer;
		_instrument = NULL;
	}

	if (_instrument != NULL) {
		delete _instrument;
		_instrument = NULL;
	}
}

void MusicPlayer::setMusicSheet(MusicSheet data)
{
	_musicSheet = data;
}

int MusicPlayer::setInstrument(InstrumentType value)
{
	if (_instrument != NULL) {
		delete _instrument;
		_instrument = NULL;
	}

	switch (value)
	{
	case MusicPlayer::BELL:
		_instrumentType = BELL;
//		_instrument = new Bell; // todo: impliment bell class
		break;
	case MusicPlayer::FLUTE:
		_instrumentType = FLUTE;
		_instrument = new Flute;
		break;
	case MusicPlayer::HORN:
		_instrumentType = HORN;
//		_instrument = new Horn; // todo: impliment horn class
		break;
	default:
		break;
	}
	return 0;
}

int MusicPlayer::getTempo()
{
	return _musicSheet.tempo;
}

MusicPlayer::InstrumentType MusicPlayer::getInstrumentType()
{
	return _instrumentType;
}

float MusicPlayer::getTimeSignature()
{
	return _musicSheet.timeSignature;
}

QString MusicPlayer::instrumentTypeToQString(InstrumentType)
{
	switch (_instrumentType)
	{
	case MusicPlayer::BELL:
		return "Bell";
		break;
	case MusicPlayer::FLUTE:
		return "Flute";
		break;
	case MusicPlayer::HORN:
		return "Horn";
		break;
	default:
		break;
	}
	return 0;
}

int MusicPlayer::playSong()
{
	if (_isPlaying == true) {
		return 1;
	}

	if (_timer == NULL)
	{
		_timer = new QTimer();
		_timer->setInterval(_tickRate);
		connect(_timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
		_tickCounter = 0;
		_noteCounter = 0;
	}

	_isPlaying = true;
	_timer->start();

	return 0;
}

int MusicPlayer::stopSong()
{
	if (!_isPlaying) {
		return 1;
	}

	_isPlaying = false;
	_timer->stop();
	delete _timer;
	_timer = NULL;

	_instrument->switchOctave(1);

	return 0;
}

int MusicPlayer::pauseSong()
{
	_timer->stop();
	_isPlaying = false;
	return 0;
}

void MusicPlayer::timerTimeout()
{
	_tickCounter--;

	if (_tickCounter > 0) {
		return;
	}

	int beatDuration = 60 * 1000 / _musicSheet.tempo;

	switch (_musicSheet.notes.at(_noteCounter))
	{
	case NULL:
		for (int scan = 1; scan + _noteCounter < _musicSheet.notes.size(); scan++)
		{
			switch (_musicSheet.notes.at(_noteCounter+scan))
			{
			case 0:
				continue;
				break;

			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				scan = _musicSheet.notes.size();
				break;

			case 'w': case 'h': case 'q': case 'e': case 's':
			case 't': case 'S':
				_instrument->stopNote();
				break;

			default:
				break;
			}
		}
		break;

	case '0': _tickCounter = 1; _instrument->playNote(0); break;
	case '1': _tickCounter = 1; _instrument->playNote(1); break;
	case '2': _tickCounter = 1; _instrument->playNote(2); break;
	case '3': _tickCounter = 1; _instrument->playNote(3); break;
	case '4': _tickCounter = 1; _instrument->playNote(4); break;
	case '5': _tickCounter = 1; _instrument->playNote(5); break;
	case '6': _tickCounter = 1; _instrument->playNote(6); break;
	case '7': _tickCounter = 1; _instrument->playNote(7); break;
	case '8': _tickCounter = 1; _instrument->playNote(8); break;
	case '9': _tickCounter = 1; _instrument->playNote(9); break;
	default: break;
	}

	switch (_musicSheet.notes.at(_noteCounter))
	{
	case 'w': _tickCounter = (beatDuration * _musicSheet.timeSignature * 4) / _tickRate; break;
	case 'h': _tickCounter = (beatDuration * _musicSheet.timeSignature * 2) / _tickRate; break;
	case 'q': _tickCounter = beatDuration * 1 / _tickRate; break;
	case 'e': _tickCounter = beatDuration / 2 / _tickRate; break;
	case 's': _tickCounter = beatDuration / 4 / _tickRate; break;
	case 't': _tickCounter = beatDuration / 8 / _tickRate; break;
	case 'S': _tickCounter = beatDuration / 16 / _tickRate; break;
	case 'L': _tickCounter = 1; _instrument->switchOctave(1); break;
	case 'M': _tickCounter = 1; _instrument->switchOctave(2); break;
	case 'H': _tickCounter = 1; _instrument->switchOctave(3); break;
	default: break;
	}

	_noteCounter++;
}

#include "stdafx.h"
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(void)
	: _timer (NULL), _tickRate(25), _isPlaying(false)
{
}

MusicPlayer::~MusicPlayer(void)
{
	if (_timer) {
		delete _timer;
	}
}

void MusicPlayer::setMusicSheet(MusicSheet data)
{
	_musicSheet = data;
}

int MusicPlayer::setInstrument(InstrumentType value)
{
	switch (value)
	{
	case MusicPlayer::BELL:
		_instrumentType = BELL;
		// todo load Bell
		break;
	case MusicPlayer::FLUTE:
		_instrumentType = FLUTE;
		// todo load Flute
		break;
	case MusicPlayer::HORN:
		_instrumentType = HORN;
		// todo load Horn
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

	// todo:
	//  set instrument to lowest octave

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

	qDebug() << _musicSheet.notes.at(_noteCounter);

	int beatDuration = 60 * 1000 / _musicSheet.tempo;

	switch (_musicSheet.notes.at(_noteCounter))
	{
	case NULL:
		for (int forward = 1; _noteCounter + forward < _musicSheet.notes.size(); forward++)
		{
			switch (_musicSheet.notes.at(_noteCounter + forward))
			{
				case '1': case '2': case '3': case '4': case '5':
				case '6': case '7': case '8': case '9': case '0':
					forward = _musicSheet.notes.size();
					break;
				case 'w': case 'h': case 'q': case 's': case 't': case 'S':
					// todo: stop current note
					forward = _musicSheet.notes.size();
					break;
			default:
				break;
			}
		}
		break;

	case '0': _tickCounter = 1; break;
	case '1': _tickCounter = 1; break;
	case '2': _tickCounter = 1; break;
	case '3': _tickCounter = 1; break;
	case '4': _tickCounter = 1; break;
	case '5': _tickCounter = 1; break;
	case '6': _tickCounter = 1; break;
	case '7': _tickCounter = 1; break;
	case '8': _tickCounter = 1; break;
	case '9': _tickCounter = 1; break;
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
	case 'L': _tickCounter = 1; break;
	case 'M': _tickCounter = 1; break;
	case 'H': _tickCounter = 1; break;
	default: break;
	}

	_noteCounter++;
}

#ifndef __MUSIC_PLAYER_H__
#define __MUSIC_PLAYER_H__

class MusicPlayer : public QObject
{
	Q_OBJECT

public:
	MusicPlayer(void);
	~MusicPlayer(void);

	enum InstrumentType {
		BELL, FLUTE, HORN 
	};

	struct MusicSheet {
		int tempo;
		float timeSignature;
		std::vector <char> notes;
	};

public:
	// setters
	void setMusicSheet(MusicSheet);
	int setInstrument(InstrumentType);

	// getters
	int getTempo();
	float getTimeSignature();
	InstrumentType getInstrumentType();

	// utility
	QString instrumentTypeToQString(InstrumentType);

	// controller
	int playSong(), stopSong(), pauseSong();

	// play timer variables and functions
private slots:
	void timerTimeout();

private:
	QTimer* _timer;
	int _tickRate, _tickCounter, _noteCounter;

	MusicSheet _musicSheet;
	InstrumentType _instrumentType;
	bool _isPlaying;
};

#endif // __MUSIC_PLAYER_H__

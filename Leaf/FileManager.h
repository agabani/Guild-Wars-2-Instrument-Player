#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include "MusicPlayer.h"

int loadSong(QString path, MusicPlayer *object);

class FileManager
{
public:
	static int loadSong(QString path, MusicPlayer&);

private:
	static QString getValue (QString& text, QString term);
	static int getMusicSheet (QString &text, std::vector <char> &sheet);
};

#endif // __FILE_MANAGER_H__

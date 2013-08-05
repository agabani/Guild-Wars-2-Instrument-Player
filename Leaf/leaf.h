#ifndef LEAF_H
#define LEAF_H

#include <QtWidgets/QMainWindow>
#include "ui_leaf.h"

#include "MusicPlayer.h"

class Leaf : public QMainWindow
{
	Q_OBJECT

public:
	Leaf(QWidget *parent = 0);
	~Leaf();

private slots:
	void doLoadMusicSheet();
	void doRefresh();
	void showAboutWindow();
	void showAboutQtWindow();
	void showPreferenceWindow();

private:
	void reloadFileList();

private:
	Ui::LeafClass ui;
	QFileSystemModel model;

private:
	MusicPlayer musicPlayer;

private: // Windows Keyboard Hook
	static HHOOK hHook;
	void UpdateKeyState(BYTE *keystate, int keycode);
	static LRESULT CALLBACK lowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // LEAF_H

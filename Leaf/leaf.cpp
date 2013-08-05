#include "stdafx.h"
#include "leaf.h"
#include "about.h"
#include "preference.h"

// Remove following header
#include "FileManager.h"

Leaf::Leaf(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	reloadFileList();
}

HHOOK Leaf::hHook(NULL);

Leaf::~Leaf()
{

}

void Leaf::UpdateKeyState(BYTE *keystate, int keycode)
{
	keystate[keycode] = GetKeyState(keycode);
}

LRESULT CALLBACK Leaf::lowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT cKey = *reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
	
	wchar_t buffer[5];

	BYTE keyboard_state[256];
	GetKeyboardState(keyboard_state);
//	UpdateKeyState(keyboard_state, VK_END);
//	UpdateKeyState(keyboard_state, VK_HOME);
//	UpdateKeyState(keyboard_state, VK_CONTROL);
//	UpdateKeyState(keyboard_state, VK_MENU);

	HKL keyboard_layout = GetKeyboardLayout(0);

	char lpszName[0x100] = {0};

	DWORD dwMsg = 1;
	dwMsg += cKey.scanCode << 16;
	dwMsg += cKey.flags << 24;

	int i = GetKeyNameText(dwMsg, (LPTSTR)lpszName, 255);

	int result = ToUnicodeEx(cKey.vkCode, cKey.scanCode, keyboard_state, buffer, 4, 0, keyboard_layout);
	buffer[4] = L'\0';

#ifdef __DEBUG__
	qDebug() << "Key: " << cKey.vkCode << " " << QString::fromUtf16((ushort*)buffer) << " " << QString::fromUtf16((ushort*)lpszName) << "\n";
#endif // __DEBUG__

	if (QString::fromUtf16((ushort*)lpszName) == "END")
	{
		UnhookWindowsHookEx(hHook);
		hHook = NULL;
		return NULL;
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

void Leaf::doLoadMusicSheet()
{
	QModelIndexList list = ui.musicTreeView->selectionModel()->selectedIndexes();
	QFileInfo fileInfo = model.fileInfo(list.at(0));
	
	if (!fileInfo.isFile())
		return;

	if (fileInfo.suffix() != "lms") 
		return;

	QString fileLocation = fileInfo.path() + "/" + fileInfo.fileName();

	// todo: Remove QString to string, and use only QString
	loadSong(fileLocation.toLocal8Bit().constData(), &musicPlayer);

	ui.songTextBrowser->setText(fileInfo.baseName());
	ui.tempoTextBrowser->setText(QString::number(musicPlayer.getTempo()));
	ui.measureTextBrowser->setText(QString::number(musicPlayer.getMeasure()));
	ui.instrumentTextBrowser->setText(musicPlayer.getInstrumentName().c_str());

	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, &Leaf::lowLevelKeyBoardProc, NULL, 0);
	if (hHook == NULL)
	{
		qDebug() << "Hook failed\n";
	}

}

void Leaf::doRefresh()
{
	reloadFileList();
}

void Leaf::showAboutWindow()
{
	About about;
	about.exec();
}

void Leaf::showAboutQtWindow()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void Leaf::showPreferenceWindow()
{
	Preference preference;
	preference.exec();
}

void Leaf::reloadFileList()
{
	model.setRootPath(QDir::currentPath());

	ui.musicTreeView->setModel(&model);
	ui.musicTreeView->setRootIndex(model.index(QDir::currentPath().append("/Library")));

	ui.musicTreeView->header()->hide();
	ui.musicTreeView->hideColumn(1);
	ui.musicTreeView->hideColumn(2);
	ui.musicTreeView->hideColumn(3);
}

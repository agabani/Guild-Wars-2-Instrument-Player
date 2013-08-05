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

Leaf::~Leaf()
{

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

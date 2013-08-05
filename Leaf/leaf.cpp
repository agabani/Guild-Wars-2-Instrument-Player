#include "stdafx.h"
#include "leaf.h"
#include "about.h"
#include "preference.h"

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

//	QMessageBox::about(this, "Debug", fileInfo.suffix());
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

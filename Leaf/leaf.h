#ifndef LEAF_H
#define LEAF_H

#include <QtWidgets/QMainWindow>
#include "ui_leaf.h"

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
};

#endif // LEAF_H

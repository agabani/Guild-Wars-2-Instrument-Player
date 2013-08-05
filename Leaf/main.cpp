#include "stdafx.h"
#include "leaf.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Leaf w;
	w.show();
	return a.exec();
}

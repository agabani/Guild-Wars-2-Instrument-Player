#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QDialog>
#include "ui_preference.h"

class Preference : public QDialog
{
	Q_OBJECT

public:
	Preference(QWidget *parent = 0);
	~Preference();

private:
	Ui::Preference ui;
};

#endif // PREFERENCE_H

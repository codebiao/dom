#pragma once

#include <QMainWindow>
#include "ui_show.h"

class show : public QMainWindow
{
	Q_OBJECT

public:
	show(QWidget *parent = nullptr);
	~show();

private:
	Ui::showClass ui;
};

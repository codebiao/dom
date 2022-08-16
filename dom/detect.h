#pragma once

#include <QMainWindow>
#include "ui_detect.h"

class detect : public QMainWindow
{
	Q_OBJECT

public:
	detect(QWidget *parent = nullptr);
	~detect();

private:
	Ui::detectClass ui;
};

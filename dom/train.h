#pragma once

#include <QMainWindow>
#include "ui_train.h"

class train : public QMainWindow
{
	Q_OBJECT

public:
	train(QWidget *parent = nullptr);
	~train();

private:
	Ui::trainClass ui;
};

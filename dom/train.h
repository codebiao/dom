#pragma once

#include <QMainWindow>
#include "ui_train.h"
#include<QDebug>
class train : public QMainWindow
{
	Q_OBJECT

public:
	train(QWidget *parent = nullptr);
	~train();

public slots:
	void test();

private:
	Ui::trainClass ui;
};

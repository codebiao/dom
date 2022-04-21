#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_operator_window.h"
#include "qdebug.h"
#include <QCloseEvent>
class operator_window : public QWidget
{
	Q_OBJECT

public:
	operator_window(QWidget *parent = Q_NULLPTR);
	~operator_window();
	

public slots:
	void selectAlgorithm(QString currentText);	//选择算子

signals:
	void seedData(QString);		////用来传递数据的信号

public:
	Ui::operator_window ui;			//改为public，给主界面调用
};

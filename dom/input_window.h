#pragma once
#include"GlobalParam.h"
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include "ui_input_window.h"
#include <qdebug.h>
#include <QTextBlock>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "GlobalParam.h"
#include "CodeFactory.h"

using namespace cv;
using namespace std;

class input_window : public QMainWindow
{
	Q_OBJECT

public:
	input_window(QWidget *parent = Q_NULLPTR);
	~input_window();
	QStringList getFunInfo(QString str);	//将函数信息 QString -> QStringList[ funName , param1, param2, ...]

public slots:
	void run();		//运行
	void receiveData(QString data);		//接收operator_window传递过来的数据的槽
signals:
	void updateToVariate();				//让变量窗口更新数据
private:
	Ui::input_window ui;
};

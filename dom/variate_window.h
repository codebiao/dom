#pragma once
#include <QMainWindow>
#include "ui_variate_window.h"
#include<qdebug.h>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "QFlowLayout.h"
#include "GlobalParam.h"
#include <QLabel>
#include "VariateLabel.h"

using namespace cv;
using namespace std;

class variate_window : public QMainWindow
{
	Q_OBJECT

public:
	variate_window(QWidget *parent = Q_NULLPTR);
	~variate_window();
	
public slots:
	void update();						//更新数值
	void LabelTrans2Window(Mat mat);	//中转站  //Label里的signal，转到该槽函数中进行处理
signals:
	void sendMat2OutputWindow(Mat);		//将Mat数据发送到OutputWindow中

public:
	Ui::variate_window ui;
	QFlowLayout* flowLayout;			//布局
};

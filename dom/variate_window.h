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
	void update();						//������ֵ
	void LabelTrans2Window(Mat mat);	//��תվ  //Label���signal��ת���òۺ����н��д���
signals:
	void sendMat2OutputWindow(Mat);		//��Mat���ݷ��͵�OutputWindow��

public:
	Ui::variate_window ui;
	QFlowLayout* flowLayout;			//����
};

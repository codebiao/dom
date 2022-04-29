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
	QStringList getFunInfo(QString str);	//��������Ϣ QString -> QStringList[ funName , param1, param2, ...]

public slots:
	void run();		//����
	void receiveData(QString data);		//����operator_window���ݹ��������ݵĲ�
signals:
	void updateToVariate();				//�ñ������ڸ�������
private:
	Ui::input_window ui;
};

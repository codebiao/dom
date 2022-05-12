#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_operator_window.h"
#include "qdebug.h"
#include <QCloseEvent>
#include <QComboBox>
#include "GlobalParam.h"
#include <QFileDialog>

class operator_window : public QWidget
{
	Q_OBJECT

public:
	operator_window(QWidget *parent = Q_NULLPTR);
	~operator_window();
protected:
	//��д�رպ���
	void closeEvent(QCloseEvent *e);

public slots:		
	void selectAlgorithm(QString currentText);			//ѡ������
	void openImage();									//read_imageҳ���еġ���ͼƬ��ͼ�꣬�����ļ�·����ʾ��comobox��
signals:
	void seedData(QString);		////�����������ݵ��ź�

public:
	Ui::operator_window ui;
};

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
	void selectAlgorithm(QString currentText);	//ѡ������

signals:
	void seedData(QString);		////�����������ݵ��ź�

public:
	Ui::operator_window ui;			//��Ϊpublic�������������
};

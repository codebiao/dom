#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_operator_window.h"
#include "qdebug.h"
#include <QCloseEvent>
#include <QComboBox>

struct operatorInfoStruct {
	QString currentIndex;	//��ǰstackedWidget��ҳ������
	QString title;			//���ӱ���
	QString intro;			//���ӽ���
};
class operator_window : public QWidget
{
	Q_OBJECT

public:
	operator_window(QWidget *parent = Q_NULLPTR);
	~operator_window();
	

public slots:		
	void selectAlgorithm(QString currentText);									//ѡ������
	void readTxt2Map(QString filePath, QMap<QString, operatorInfoStruct> &Map); //��ȡ�ļ�����Map��//�������������뵽comBox��
signals:
	void seedData(QString);		////�����������ݵ��ź�

public:
	Ui::operator_window ui;
	QMap<QString, operatorInfoStruct> operatorInfoMap;
};

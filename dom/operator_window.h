#pragma once
#pragma execution_character_set("utf-8")
#include <QWidget>
#include "ui_operator_window.h"
#include "qdebug.h"
#include <QCloseEvent>
#include <QComboBox>

struct operatorInfoStruct {
	QString currentIndex;	//当前stackedWidget的页面索引
	QString title;			//算子标题
	QString intro;			//算子介绍
};
class operator_window : public QWidget
{
	Q_OBJECT

public:
	operator_window(QWidget *parent = Q_NULLPTR);
	~operator_window();
	

public slots:		
	void selectAlgorithm(QString currentText);									//选择算子
	void readTxt2Map(QString filePath, QMap<QString, operatorInfoStruct> &Map); //读取文件存入Map中//并将函数名加入到comBox中
signals:
	void seedData(QString);		////用来传递数据的信号

public:
	Ui::operator_window ui;
	QMap<QString, operatorInfoStruct> operatorInfoMap;
};

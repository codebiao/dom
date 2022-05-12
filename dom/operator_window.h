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
	//重写关闭函数
	void closeEvent(QCloseEvent *e);

public slots:		
	void selectAlgorithm(QString currentText);			//选择算子
	void openImage();									//read_image页面中的“打开图片”图标，并将文件路径显示在comobox中
signals:
	void seedData(QString);		////用来传递数据的信号

public:
	Ui::operator_window ui;
};

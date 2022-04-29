#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMainWindow>
#include "ui_output_window.h"
#include <qdebug.h>
#include "GlobalParam.h"
#include <QCloseEvent>
class output_window : public QMainWindow
{
	Q_OBJECT

public:
	output_window(QWidget *parent = Q_NULLPTR);
	~output_window();
protected:
	//ÖØÐ´¹Ø±Õº¯Êý
	void closeEvent(QCloseEvent *e);
public slots:
	void showMat(Mat mat);

private:
	Ui::output_window ui;
};

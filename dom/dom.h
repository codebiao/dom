#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_dom.h"
#include "operator_window.h"
#include "input_window.h"
#include "output_window.h"
#include "variate_window.h"
#include "code.h"
#include<QDebug>
#include<map> 


class dom : public QMainWindow
{
    Q_OBJECT

public:
    dom(QWidget *parent = Q_NULLPTR);		
	bool isOpen(QString windowTitle);		//判断窗口是否已经打开
	QImage cvMat2QImage(const cv::Mat& mat);//将Mat类型转化成Qimage

public slots:
	void open_operator_window();		//打开 算子窗口
	void open_input_window();			//打开 输入窗口
	void open_output_window();			//打开 输出窗口
	void open_variate_window();			//打开 变量窗口


	void image_stitch();				//调出参数控件、链接"应用"按钮（图像预处理--图像拼接 算子）
	void image_segmentation();			//调出参数控件、链接"应用"按钮（图像预处理--图像分割 算子）
	void test();//测试传值


public:
    Ui::domClass ui;
	operator_window *operatorWindow;	//算子窗口 对象
	input_window* inputWindow;			//输入窗口 对象
	output_window* outputWindow;		//输出窗口 对象
	variate_window* variateWindow;		//变量窗口 对象

};

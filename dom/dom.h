#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMainWindow>
#include "ui_dom.h"
#include "operator_window.h"
#include "input_window.h"
#include "output_window.h"
#include "variate_window.h"
#include<QDebug>
#include<map> 
#include <QMessageBox>

class dom : public QMainWindow
{
    Q_OBJECT

public:
    dom(QWidget *parent = Q_NULLPTR);		
	bool isOpen(QString windowTitle);		//�жϴ����Ƿ��Ѿ���
	QImage cvMat2QImage(const cv::Mat& mat);//��Mat����ת����Qimage

public slots:
	void open_operator_window();		//�� ���Ӵ���
	void open_input_window();			//�� ���봰��
	void open_output_window();			//�� �������
	void open_variate_window();			//�� ��������

	void set_data2operator_comboBox(QString str);	//ͨ������˵��еġ����ӡ�������operatorWindow�е�QComboBox��	
	void receiveException(QString exception);		//�õ�input���ڴ����Ĵ�����Ϣ

public:
    Ui::domClass ui;
	operator_window *operatorWindow;	//���Ӵ��� ����
	input_window* inputWindow;			//���봰�� ����
	output_window* outputWindow;		//������� ����
	variate_window* variateWindow;		//�������� ����

	//���ѧϰ






};

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
	bool isOpen(QString windowTitle);		//�жϴ����Ƿ��Ѿ���
	QImage cvMat2QImage(const cv::Mat& mat);//��Mat����ת����Qimage

public slots:
	void open_operator_window();		//�� ���Ӵ���
	void open_input_window();			//�� ���봰��
	void open_output_window();			//�� �������
	void open_variate_window();			//�� ��������


	void image_stitch();				//���������ؼ�������"Ӧ��"��ť��ͼ��Ԥ����--ͼ��ƴ�� ���ӣ�
	void image_segmentation();			//���������ؼ�������"Ӧ��"��ť��ͼ��Ԥ����--ͼ��ָ� ���ӣ�
	void test();//���Դ�ֵ


public:
    Ui::domClass ui;
	operator_window *operatorWindow;	//���Ӵ��� ����
	input_window* inputWindow;			//���봰�� ����
	output_window* outputWindow;		//������� ����
	variate_window* variateWindow;		//�������� ����

};

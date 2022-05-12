#pragma once
#pragma execution_character_set("utf-8")
#include <QMainWindow>
#include <QTextBlock>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "qdebug.h"
#include <QLabel>
using namespace cv;
using namespace std;


//QMapʹ��
// https://www.csdn.net/tags/MtTaMgysNjEwMTA2LWJsb2cO0O0O.html
//

//������Ϣ�ṹ�� //ȫΪ QString ���ó�������ת
struct operatorInfoStruct {
	QString functionName;	//������
	QString currentIndex;	//��ǰstackedWidget��ҳ������
	QString title;			//���ӱ���
	QString intro;			//���ӽ���
	QString inputLen;		//����Mat�ĸ���
	QString outputLen;		//���Mat�ĸ���
};
//����������ṹ��
struct regionStruct {
	QString regionName;		//������
	Mat regionMat;			//����Matֵ
};

//**********ȫ�ֱ���***********/


extern QList<operatorInfoStruct> global_operatorInfoList;	//������ϢList�����txt������������
extern QList<regionStruct> global_regionList;				//�������ڡ�����List



//**********ȫ�ַ���***********/
		
//��Mat��ʾ��Label��
extern  void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat);	
//��ȡtxt�ļ���������ȡ������Ϣ����QList��
extern	QList<operatorInfoStruct> readTxt2operatorInfoList(QString filePath);
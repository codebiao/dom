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


//QMap使用
// https://www.csdn.net/tags/MtTaMgysNjEwMTA2LWJsb2cO0O0O.html
//

//算子信息结构体 //全为 QString ，拿出数据再转
struct operatorInfoStruct {
	QString functionName;	//函数名
	QString currentIndex;	//当前stackedWidget的页面索引
	QString title;			//算子标题
	QString intro;			//算子介绍
	QString inputLen;		//输入Mat的个数
	QString outputLen;		//输出Mat的个数
};
//变量、区域结构体
struct regionStruct {
	QString regionName;		//区域名
	Mat regionMat;			//区域Mat值
};

//**********全局变量***********/


extern QList<operatorInfoStruct> global_operatorInfoList;	//算子信息List，存放txt读出来的数据
extern QList<regionStruct> global_regionList;				//变量窗口、区域List



//**********全局方法***********/
		
//把Mat显示在Label中
extern  void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat);	
//读取txt文件，并将读取到的信息加入QList中
extern	QList<operatorInfoStruct> readTxt2operatorInfoList(QString filePath);
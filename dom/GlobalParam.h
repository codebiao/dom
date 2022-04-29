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

//全为 QString ，拿出数据再转
struct operatorInfoStruct {
	QString functionName;	//函数名
	QString currentIndex;	//当前stackedWidget的页面索引
	QString title;			//算子标题
	QString intro;			//算子介绍
	QString inputLen;		//输入Mat的个数
	QString outputLen;		//输出Mat的个数
};

//定义全局变量
extern QMap<QString, Mat> RegionMap;						//区域Map
extern QList<operatorInfoStruct> global_operatorInfoList;	//算子信息Map，存放txt读出来的数据

//清空RegionMap
extern  void  clearRegionMap();			
//把Mat显示在Label中
extern  void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat);	
//读取txt文件，并将读取到的信息加入QList中
extern	QList<operatorInfoStruct> readTxt2Map(QString filePath);
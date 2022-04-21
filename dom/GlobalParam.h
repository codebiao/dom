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

//定义全局变量
extern QMap<QString, Mat> RegionMap;
extern  void  clearRegionMap();			////清空RegionMap
extern  void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat);	//把Mat现实中在Label中
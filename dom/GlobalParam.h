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

//����ȫ�ֱ���
extern QMap<QString, Mat> RegionMap;
extern  void  clearRegionMap();			////���RegionMap
extern  void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat);	//��Mat��ʵ����Label��
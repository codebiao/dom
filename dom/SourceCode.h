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
  
/************************************ 源代码库，所有的 openCV 算子******************************/

/*---------------------------- 0 input, 1 output ---------------------------------------------*/
//读取图片
void read_image(Mat &out, string filePath);

/*---------------------------- 1 input, 1 output ---------------------------------------------*/
//图像分割 基于边缘
//基于canny算子的 边缘检测
void image_segmentation(Mat src, Mat &out, int thresh);

/*---------------------------- 2 input, 1 output ---------------------------------------------*/
void image_stitch(Mat src1, Mat src2, Mat &out);
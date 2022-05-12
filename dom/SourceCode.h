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
  
/************************************ Դ����⣬���е� openCV ����******************************/

/*---------------------------- 0 input, 1 output ---------------------------------------------*/
//��ȡͼƬ
void read_image(Mat &out, string filePath);

/*---------------------------- 1 input, 1 output ---------------------------------------------*/
//ͼ��ָ� ���ڱ�Ե
//����canny���ӵ� ��Ե���
void image_segmentation(Mat src, Mat &out, int thresh);

/*---------------------------- 2 input, 1 output ---------------------------------------------*/
void image_stitch(Mat src1, Mat src2, Mat &out);
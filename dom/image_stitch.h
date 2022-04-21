#pragma once

#include <QObject>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
using namespace cv::xfeatures2d;
#include <opencv2/calib3d.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include<opencv2/nonfree/nonfree.hpp>
//#include<opencv2/legacy/legacy.hpp>
#include<vector>
using namespace std;
using namespace cv;

class image_stitch : public QObject
{
	Q_OBJECT

public:
	image_stitch(QObject *parent);
	~image_stitch();

	//„–÷µ∆¥Ω”
	void stitch_1(QString text);
	Mat stitch_2(Mat img, Mat img2);

};

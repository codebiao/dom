#include "SourceCode.h"


//��ȡͼƬ
void read_image(Mat & out, string filePath)
{
	out = imread(filePath);
}

/*
 * ͼ��ָ� ���ڱ�Ե
 * ����canny���ӵ� ��Ե���
 * https://www.cnblogs.com/xinxue/p/5350746.html
*/
void  image_segmentation(Mat src, Mat &out, int thresh)
{
	RNG rng(12345);
	// ��ͼ
	//src = imread("F://Desktop//55.png", IMREAD_COLOR);
	//if (src.empty());

	// ת��Ϊ�Ҷ�ͼ
	Mat src_gray;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	// ��ʾ
	//namedWindow("Source", WINDOW_AUTOSIZE);
	//imshow("Source", src);

	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// canny ��Ե���
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);

	// Ѱ������
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

	// ��������
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point());
	}
	//���
	out = drawing;
}
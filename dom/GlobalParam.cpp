#include "GlobalParam.h"


QMap<QString, Mat> RegionMap;

//���RegionMap
void clearRegionMap() {
	qDebug() << "--------------clearRegionMap����------------";
	for (auto iter = RegionMap.begin(); iter != RegionMap.end();)
	{
		iter = RegionMap.erase(iter);
	}

}

////��Mat��ʵ����Label��
void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat)
{
	cv::Mat Rgb;
	QImage Img;
	if (mat.channels() == 3)//RGB Img
	{
		cv::cvtColor(mat, Rgb, CV_BGR2RGB);//��ɫ�ռ�ת��
		Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
	}
	else//Gray Img
	{
		Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
	}
	label->setPixmap(QPixmap::fromImage(Img).scaled(label->size()));
}

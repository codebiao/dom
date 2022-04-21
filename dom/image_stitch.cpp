#include "image_stitch.h"

image_stitch::image_stitch(QObject *parent)
	: QObject(parent)
{
}

image_stitch::~image_stitch()
{
}

//��ֵƴ��
void image_stitch::stitch_1(QString text)
{
	qDebug() << text << endl;
}

/* �������㷨
 * ���㷨��������ƥ�䣬��һ��ƥ�����ʹ��ǰ���ֵ�ƥ���㷨���ڶ���ƥ��ʱ��ʹ�õ�ƥ���㷨��ִ��˳�����һ��ƥ���˳���෴��
 * ���ڶ���ͼ���ÿ���ؼ���������һ��ͼ���ȫ���ؼ�����бȽϡ�
 * ֻ�����������϶�ƥ�䵽��ͬһ�������㣬����Ϊ��һ����Ч��ƥ��ԡ�
 * ��ַ: https://www.cnblogs.com/skyfsm/p/7411961.html
*/
void symmetryTest(std::vector<cv::DMatch>& matches1, std::vector<cv::DMatch>& matches2, std::vector<cv::DMatch>& symMatches);
//��ѡƥ���
vector<DMatch> chooseGood(Mat descriptor, vector<DMatch> matches);
//�Ż���ͼ�����Ӵ���ʹ��ƴ����Ȼ
void OptimizeSeam(Mat& img1, Mat& trans, Mat& dst);
void CalcCorners(const Mat& H, const Mat& src);

typedef struct
{
	Point2f left_top;
	Point2f left_bottom;
	Point2f right_top;
	Point2f right_bottom;
}four_corners_t;
four_corners_t corners;

Mat image_stitch::stitch_2(Mat img, Mat img2) {
	qDebug("start~~");

	//const char* imagename = "F://Desktop//1.png";//��
	//��QString���͵�ȫ�ֱ���address_1ת����String����
	//const char* image_1 = "F://Desktop//1.png";//��
	//const char* image_2 = "F://Desktop//2.png";//��
	//���ļ��ж���ͼ��
	//Mat img = imread(image_1);	//��
	//if(image_2==NULL) image_2 = "F://Desktop//2.png";
	//image_2 = "F://Desktop//2.png";
	//Mat img2 = imread(image_2);	//��
	//��ʾ���

	//��ʾ��ʼͼ��
	//namedWindow("image before", 0);
	//imshow("image before", img);
	//namedWindow("image2 before", 0);
	//imshow("image2 before", img2);

	//sift�������
	Ptr<SiftFeatureDetector> siftdtc = SiftFeatureDetector::create();// ����������ֵ
	vector<KeyPoint>kp1, kp2;

	siftdtc->detect(img, kp1);

	Mat outimg1;
	drawKeypoints(img, kp1, outimg1);
	//imshow("image1 keypoints",outimg1);

	siftdtc->detect(img2, kp2);
	Mat outimg2;
	drawKeypoints(img2, kp2, outimg2);
	//imshow("image2 keypoints",outimg2);

	//�ڼ�⵽������������������������

	Ptr<SiftDescriptorExtractor> extractor = SiftDescriptorExtractor::create();
	Mat descriptor1, descriptor2;
	extractor->compute(img, kp1, descriptor1);  //��һ��������
	extractor->compute(img2, kp2, descriptor2);  //�ڶ���������

	FlannBasedMatcher matcher;
	//BFMatcher matcher;
	//vector<Mat> train_dest_collection(1,descriptor1);
	//matcher.add(train_dest_collection);
	//matcher.train();

	vector<DMatch> matches1, matches2;   //�������Ӷ���
	matcher.match(descriptor1, descriptor2, matches1);  //����ƥ���
	matcher.match(descriptor2, descriptor1, matches2);
	//ƥ��
	vector<DMatch> goodMatches1, goodMatches2, symMatches;
	goodMatches1 = chooseGood(descriptor1, matches1);
	goodMatches2 = chooseGood(descriptor2, matches2);

	Mat img_matches;
	symmetryTest(goodMatches1, goodMatches2, symMatches);
	drawMatches(img, kp1, img2, kp2, symMatches, img_matches);
	//namedWindow("matches", WINDOW_NORMAL);
	//imshow("matches", img_matches);

	/*ͼ����׼*/
	//���Ƚ��㼯ת��ΪPoint2f����
	vector<Point2f> imagePoints1, imagePoints2;

	for (int i = 0; i < symMatches.size(); i++)
	{
		imagePoints2.push_back(kp1[symMatches[i].queryIdx].pt);
		imagePoints1.push_back(kp2[symMatches[i].trainIdx].pt);
	}
	//��ʼʵ����׼
	//��ȡͼ��1��ͼ��2��ͶӰӳ����� �ߴ�Ϊ3*3
	Mat homo = findHomography(imagePoints1, imagePoints2, FM_RANSAC);
	//Ҳ����ʹ��getPerspectiveTransform�������͸�ӱ任���󣬲���Ҫ��ֻ����4���㣬Ч���Բ�
		//Mat   homo=getPerspectiveTransform(imagePoints1,imagePoints2);
	cout << "�任����Ϊ��\n" << homo << endl << endl; //���ӳ�����

	//������׼ͼ���ĸ���������
	CalcCorners(homo, img2);
	cout << "left_top:" << corners.left_top << endl;
	cout << "left_bottom:" << corners.left_bottom << endl;
	cout << "right_top:" << corners.right_top << endl;
	cout << "right_bottom:" << corners.right_bottom << endl;

	//ͼ����׼
	Mat imageTransform1, imageTransform2;
	warpPerspective(img2, imageTransform1, homo, Size(MAX(corners.right_top.x, corners.right_bottom.x), img.rows));
	//warpPerspective(img2, imageTransform2, adjustMat*homo, Size(img.cols*1.3, img.rows*1.8));
	//imshow("ֱ�Ӿ���͸�Ӿ���任", imageTransform1);
	//imwrite("images/trans1.jpg", imageTransform1);


	//����ƴ�Ӻ��ͼ,����ǰ����ͼ�Ĵ�С
	int dst_width = imageTransform1.cols;  //ȡ���ҵ�ĳ���Ϊƴ��ͼ�ĳ���
	int dst_height = img.rows;

	Mat dst(dst_height, dst_width, CV_8UC3);
	dst.setTo(0);

	imageTransform1.copyTo(dst(Rect(0, 0, imageTransform1.cols, imageTransform1.rows)));
	img.copyTo(dst(Rect(0, 0, img.cols, img.rows)));

	//imshow("b_dst", dst);


	OptimizeSeam(img, imageTransform1, dst);

	return dst;
	//imshow("dst", dst);
	//imwrite("images/dst.jpg", dst);

	//�˺����ȴ�������������������ͷ���
	//waitKey();
}



//�Ż���ͼ�����Ӵ���ʹ��ƴ����Ȼ
void OptimizeSeam(Mat& img1, Mat& trans, Mat& dst)
{
	int start = MIN(corners.left_top.x, corners.left_bottom.x);//��ʼλ�ã����ص��������߽�

	double processWidth = img1.cols - start;//�ص�����Ŀ��
	int rows = dst.rows;
	int cols = img1.cols; //ע�⣬������*ͨ����
	double alpha = 1;//img1�����ص�Ȩ��
	for (int i = 0; i < rows; i++)
	{
		uchar* p = img1.ptr<uchar>(i);  //��ȡ��i�е��׵�ַ
		uchar* t = trans.ptr<uchar>(i);
		uchar* d = dst.ptr<uchar>(i);
		for (int j = start; j < cols; j++)
		{
			//�������ͼ��trans�������صĺڵ㣬����ȫ����img1�е�����
			if (t[j * 3] == 0 && t[j * 3 + 1] == 0 && t[j * 3 + 2] == 0)
			{
				alpha = 1;
			}
			else
			{
				//img1�����ص�Ȩ�أ��뵱ǰ�������ص�������߽�ľ�������ȣ�ʵ��֤�������ַ���ȷʵ��
				alpha = (processWidth - (j - start)) / processWidth;
			}

			d[j * 3] = p[j * 3] * alpha + t[j * 3] * (1 - alpha);
			d[j * 3 + 1] = p[j * 3 + 1] * alpha + t[j * 3 + 1] * (1 - alpha);
			d[j * 3 + 2] = p[j * 3 + 2] * alpha + t[j * 3 + 2] * (1 - alpha);

		}
	}

}
void CalcCorners(const Mat& H, const Mat& src)
{
	double v2[] = { 0, 0, 1 };//���Ͻ�
	double v1[3];//�任�������ֵ
	Mat V2 = Mat(3, 1, CV_64FC1, v2);  //������
	Mat V1 = Mat(3, 1, CV_64FC1, v1);  //������

	V1 = H * V2;
	//���Ͻ�(0,0,1)
	cout << "V2: " << V2 << endl;
	cout << "V1: " << V1 << endl;
	corners.left_top.x = v1[0] / v1[2];
	corners.left_top.y = v1[1] / v1[2];

	//���½�(0,src.rows,1)
	v2[0] = 0;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.left_bottom.x = v1[0] / v1[2];
	corners.left_bottom.y = v1[1] / v1[2];

	//���Ͻ�(src.cols,0,1)
	v2[0] = src.cols;
	v2[1] = 0;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.right_top.x = v1[0] / v1[2];
	corners.right_top.y = v1[1] / v1[2];

	//���½�(src.cols,src.rows,1)
	v2[0] = src.cols;
	v2[1] = src.rows;
	v2[2] = 1;
	V2 = Mat(3, 1, CV_64FC1, v2);  //������
	V1 = Mat(3, 1, CV_64FC1, v1);  //������
	V1 = H * V2;
	corners.right_bottom.x = v1[0] / v1[2];
	corners.right_bottom.y = v1[1] / v1[2];

}
//��ѡƥ���
vector<DMatch> chooseGood(Mat descriptor, vector<DMatch> matches)
{
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < descriptor.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}
	vector<DMatch> goodMatches;
	for (int i = 0; i < descriptor.rows; i++)
	{
		if (matches[i].distance < 3 * min_dist)
			goodMatches.push_back(matches[i]);
	}
	return goodMatches;
}
void symmetryTest(std::vector<cv::DMatch>& matches1,
	std::vector<cv::DMatch>& matches2,
	std::vector<cv::DMatch>& symMatches)
{
	// ����ͼ��1��ͼ��2��ƥ��
	for (std::vector<cv::DMatch>::const_iterator matchIterator1 = matches1.begin();
		matchIterator1 != matches1.end(); ++matchIterator1)
	{
		//  ����ͼ��2��ͼ��1��ƥ��
		for (std::vector<cv::DMatch>::const_iterator matchIterator2 = matches2.begin();
			matchIterator2 != matches2.end(); ++matchIterator2)
		{
			// ����ƥ�����
			if (matchIterator1->queryIdx == matchIterator2->trainIdx  &&
				matchIterator2->queryIdx == matchIterator1->trainIdx)
			{
				// �������ƥ�䣬�����
				symMatches.push_back(*matchIterator1);
				break;
			}
		}
	}
}
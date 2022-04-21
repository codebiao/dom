/* 
 *	Í¼Ïñ·Ö¸îËã·¨
*/
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;
class image_segmentation 
{

public:
	image_segmentation();
	~image_segmentation();
	static void segmentation_1(Mat src, Mat &out,int thresh);

};

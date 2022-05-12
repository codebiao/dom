#include "GlobalParam.h"


//算子信息Map，存放txt读出来的数据	//初始化
QList<operatorInfoStruct> global_operatorInfoList = readTxt2operatorInfoList("resource/operatorInfo.txt");
QList<regionStruct> global_regionList;	//变量窗口、区域List


////把Mat现实中在Label中
void global_matToQimageLabelShow(QLabel *label, cv::Mat &mat)
{
	cv::Mat Rgb;
	QImage Img;
	if (mat.channels() == 3)//RGB Img
	{
		cv::cvtColor(mat, Rgb, CV_BGR2RGB);//颜色空间转换
		Img = QImage((const uchar*)(Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
	}
	else//Gray Img
	{
		Img = QImage((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Indexed8);
	}
	label->setPixmap(QPixmap::fromImage(Img).scaled(label->size()));
	label->setScaledContents(true);
}

//	
/*	链接：https://blog.csdn.net/weixin_44390515/article/details/117780144
 *	读取txt文件，并将读取到的信息加入QList中
 *	txt格式为UTF-8，否则会乱码
 *	只读取txt文件中固定要求的信息：
		1、信息必须由制表符"\t"分割
		2、列数必须为6，否则不识别
 */
QList<operatorInfoStruct>  readTxt2operatorInfoList(QString filePath)
{
	QList<operatorInfoStruct>  global_operatorInfoList;
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Can't open the file!" << endl;
	}
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		QString str(line);
		QStringList list = str.split("\n", QString::SkipEmptyParts);
		if (list.length() != 0) {	//去除一些空行的信息
			list = list[0].split("\t", QString::SkipEmptyParts);
			//qDebug() << "list.length=" << list.length() << "		list=" << list << endl;
			if (list.length() == 6) {	//只选取length = 6 的正确信息
				operatorInfoStruct infoStruct;
				infoStruct.functionName = list[0];
				infoStruct.currentIndex = list[1];			//第 1 列 currentIndex		//从0开始
				infoStruct.inputLen = list[2];		//第 2 列 inputLen
				infoStruct.outputLen = list[3];		//第 3 列 outputLen
				infoStruct.title = list[4];					//第 4 列 title
				infoStruct.intro = list[5];					//第 5 列 intro
				global_operatorInfoList.append(infoStruct);			//第 0 列 functionName
				//将该函数名称加入comboBox中,插在末尾
				//ui.comboBox->insertItem(ui.comboBox->count(), list[0]);
			}
		}
	}
	file.close();
	return global_operatorInfoList;
}
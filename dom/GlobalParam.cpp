#include "GlobalParam.h"


//������ϢMap�����txt������������	//��ʼ��
QList<operatorInfoStruct> global_operatorInfoList = readTxt2operatorInfoList("resource/operatorInfo.txt");
QList<regionStruct> global_regionList;	//�������ڡ�����List


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
	label->setScaledContents(true);
}

//	
/*	���ӣ�https://blog.csdn.net/weixin_44390515/article/details/117780144
 *	��ȡtxt�ļ���������ȡ������Ϣ����QList��
 *	txt��ʽΪUTF-8�����������
 *	ֻ��ȡtxt�ļ��й̶�Ҫ�����Ϣ��
		1����Ϣ�������Ʊ��"\t"�ָ�
		2����������Ϊ6������ʶ��
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
		if (list.length() != 0) {	//ȥ��һЩ���е���Ϣ
			list = list[0].split("\t", QString::SkipEmptyParts);
			//qDebug() << "list.length=" << list.length() << "		list=" << list << endl;
			if (list.length() == 6) {	//ֻѡȡlength = 6 ����ȷ��Ϣ
				operatorInfoStruct infoStruct;
				infoStruct.functionName = list[0];
				infoStruct.currentIndex = list[1];			//�� 1 �� currentIndex		//��0��ʼ
				infoStruct.inputLen = list[2];		//�� 2 �� inputLen
				infoStruct.outputLen = list[3];		//�� 3 �� outputLen
				infoStruct.title = list[4];					//�� 4 �� title
				infoStruct.intro = list[5];					//�� 5 �� intro
				global_operatorInfoList.append(infoStruct);			//�� 0 �� functionName
				//���ú������Ƽ���comboBox��,����ĩβ
				//ui.comboBox->insertItem(ui.comboBox->count(), list[0]);
			}
		}
	}
	file.close();
	return global_operatorInfoList;
}
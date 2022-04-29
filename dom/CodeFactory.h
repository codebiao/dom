#pragma once

#include <QObject>
#include"SourceCode.h"
/************************************ 代码工厂，与源代码库一一对应******************************/

class CodeFactory : public QObject
{
	Q_OBJECT

public:
	CodeFactory(QObject *parent = nullptr);
	~CodeFactory();

/*---------------------------- 0 input, 1 output ---------------------------------------------*/
	Q_INVOKABLE Mat read_image(QList<QString> args) {
		Mat out;
		string filepath = args[0].toStdString();
		::read_image(out, filepath);
		return out;
	}

/*---------------------------- 1 input, 1 output ---------------------------------------------*/
	Q_INVOKABLE Mat image_segmentation(Mat src, QList<QString> qstringList) {
		Mat out;
		int thresh = qstringList[0].toInt();
		::image_segmentation(src, out, thresh);
		return out;
	}




















};

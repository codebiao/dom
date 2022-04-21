#include "input_window.h"
#include"operator_window.h"
#include"image_segmentation.h"

input_window::input_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//qDebug() <<"input_window= " + variateMap["a"];
	connect(ui.btn_run, SIGNAL(clicked()), this, SLOT(run()));
	
}

input_window::~input_window()
{
}

//将函数信息 QString -> QStringList[ funName , param1, param2, ...]
QStringList input_window::getFunInfo(QString str)
{
	qDebug() << "--------------getFunInfo函数------------";
	QStringList result;
	//qDebug() << "当前行的值为：" + str;
	QStringList list = str.split("(", QString::SkipEmptyParts);
	QString funName = list[0];	//获得函数名
	result.append(funName);
	qDebug() << "函数名：" << funName;
	QStringList list2 = list[1].split(")", QString::SkipEmptyParts);//(" param1, param2, param3, ...")
	QStringList list3 = list2[0].split(",");
	for (int i = 0; i < list3.count(); i++) {
		qDebug() << "参数[" << i << "]=" << list3[i];
		result.append(list3[i]);	//获得参数
	}
	qDebug() << "result: "<<result;
	return result;
}

//接收operator_window 传递过来的数据的槽函数
void input_window::receiveData(QString data)
{
	//qDebug() << "接受到数据是：" + data;
	ui.plainTextEdit->appendPlainText(data);

}


void input_window::run() {
	//开始之前先清空RegionMap
	clearRegionMap();
	//RegionMap.clear();
	//clearRegionMap();
	//qDebug() << "RegionMap.size="+ RegionMap.size();
	QTextDocument* doc = ui.plainTextEdit->document(); //文本对象
	int cnt = doc->blockCount();//每个回车符是一个 block块，一行
	for (int i = 0; i < cnt; i++)
	{
		QString str = doc->findBlockByNumber(i).text(); //文本中的一行
		str.remove(QRegExp("\\s"));		//移除所有空格
		if (str == NULL) continue;//如果没内容的话就跳过该行
		QStringList funInfo = getFunInfo(str);			//	解析str，获得函数名和参数
		//图像分割			//0-函数名 1-inRegion 2-outRegion
		if (funInfo[0] == "image_segmentation") {
			qDebug() << "--------------image_segmentation函数------------";
			//读取图片成Mat
			String image_1 = "F://Desktop//55.png";
			cv::Mat inregion = imread(image_1);
			//imshow("inregion", inregion);
			//执行函数
			Mat outRegion;								//用于接受输出Mat值
			QString outRegionName = funInfo[2];			//存入QMap的值
			image_segmentation::segmentation_1(inregion, outRegion, funInfo[3].toInt());
			//******************将输出结果存入RegionMap*****************8
			RegionMap.insert(outRegionName, outRegion);
			//imshow("outRegion", outRegion);
			//加入regionVector
			//GlobalParam::map = {"imregion",inregion};
			//GlobalParam::regionVector.append({ "imregion",inregion });
			//qDebug() << "regionVector="<< GlobalParam::regionVector;

		}else if (funInfo[0]=="") {
			
		}
	}
	//所有行执行完后，发送信号，让变量窗口更新窗口
	emit updateToVariate();
}


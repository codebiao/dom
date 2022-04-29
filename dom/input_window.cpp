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
	QTextDocument* doc = ui.plainTextEdit->document(); //文本对象
	int cnt = doc->blockCount();						//每个回车符是一个 block块，一行
	CodeFactory codeFactory;							//声明函数来源工厂
	for (int i = 0; i < cnt; i++)
	{
		QString str = doc->findBlockByNumber(i).text(); //文本中的一行
		str.remove(QRegExp("\\s"));						//移除所有空格
		if (str == NULL) continue;						//如果没内容的话就跳过该行
		QStringList funInfo = getFunInfo(str);			//解析str，获得函数名和参数
		
		//将函数名从QString -> const char *
		string stringName = funInfo[0].toStdString();
		const char * funName = stringName.c_str();

		//根据 函数名funInfo[0] 找到该函数，并取得其输入和输出的个数
		int inputNum = 0, outputNum = 0;
		for (int i = 0; i < global_operatorInfoList.size(); i++) {
			if (global_operatorInfoList[i].functionName == funInfo[0]) {
				inputNum = global_operatorInfoList[i].inputLen.toInt();
				outputNum = global_operatorInfoList[i].outputLen.toInt();
				break;
			}
		}
		//如果没找到，跳过该层循环
		if (inputNum == 0 && outputNum == 0) continue;	

/*---------------------------- 1 input, 1 output ---------------------------------------------*/
		else if (inputNum == 1 && outputNum == 1) {
			Mat out;
			QList<QString> qstringList;
			//参数0是函数名，参数1是输入名; 参数2是输出名, 从参数3开始全加入qstringList
			for (int i = 3; i < funInfo.size(); i++) {
				qstringList.append(funInfo[i]);
			}
			//从全局函数RegionMap中找到Mat
			Mat src = RegionMap.value(funInfo[1]);
			//Mat src = imread("F://Desktop//55.png");
			bool isSucce = QMetaObject::invokeMethod(
				&codeFactory, funName, Qt::DirectConnection,		//被调用对象的指针、 方法名
				Q_RETURN_ARG(Mat, out),										//返回值类型，返回值
				Q_ARG(Mat, src),
				Q_ARG(QList<QString>, qstringList));					//参数类型,参数;
			
			//******************将输出结果存入RegionMap*****************8
			if (isSucce) RegionMap.insert(funInfo[2], out);

		}

/*---------------------------- 0 input, 1 output ----read_image() 函数-----------------------------------------*/
		else if (inputNum == 0 && outputNum == 1) {
			Mat out;
			QList<QString> qstringList;
			//参数0是函数名，参数1是输出名;  从参数2开始全加入qstringList
			for (int i = 2; i < funInfo.size(); i++) {
				qstringList.append(funInfo[i]);
			}
			//qstringList.append("F://Desktop//55.png");
			bool isSucce = QMetaObject::invokeMethod(
				&codeFactory, funName, Qt::DirectConnection,		//被调用对象的指针、 方法名
				Q_RETURN_ARG(Mat, out),									//返回值类型，返回值
				Q_ARG(QList<QString>, qstringList));					//参数类型,参数;
			//******************将输出结果存入RegionMap*****************8
			if(isSucce) RegionMap.insert(funInfo[1], out);

		}

	}
	//所有行执行完后，发送信号，让变量窗口更新窗口
	emit updateToVariate();

	//遍历所有region Map






}


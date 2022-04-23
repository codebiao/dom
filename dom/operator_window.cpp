#include "operator_window.h"

operator_window::operator_window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//初始化：读取文件存入Map中//并将函数名加入到comBox中
	QString filePath = "resource/operatorInfo.txt";	//该文件在dom.qrc中添加
	readTxt2Map(filePath, operatorInfoMap);

	//当下拉框内容改变时出发selectAlgorithm函数
	connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(selectAlgorithm(QString)));
	
}

operator_window::~operator_window()
{
	qDebug("close operator_window");
}

//选择算子
void operator_window::selectAlgorithm(QString currentText) {
	qDebug() << "currentText="+ currentText;

	//按钮设为可点击
	ui.btn_apply->setEnabled(true);
	ui.btn_help->setEnabled(true);

	//根据当前Text查询Map表,取出结构体信息
	operatorInfoStruct operatorInfo = operatorInfoMap.value(currentText);
	if (operatorInfo.title != NULL) {	//QMap未查询到信息时，返回默认值，QString默认为 null //一般不会查不到
		qDebug() << "取出的结构体信息title=" + operatorInfo.title;
		ui.groupBox->setTitle(operatorInfo.title);
		qDebug() << "取出的结构体信息info=" + operatorInfo.intro;
		ui.introduce->setText(operatorInfo.intro);
		qDebug() << "取出的结构体信息currentIndex=" + operatorInfo.currentIndex;
		ui.stackedWidget->setCurrentIndex(operatorInfo.currentIndex.toInt());

		//遍历出当前页面所有QLineEdit的值	//根据QComboBox在页面中的布局， 最上面的是第一个，以此类推	//顺序和名字无关
		QList<QComboBox*> comboBoxList = ui.stackedWidget->currentWidget()->findChildren<QComboBox*>();
		for (int i = 0; i < comboBoxList.count(); ++i) {
			QComboBox* comboBox = comboBoxList.at(i);
			qDebug() << "遍历所有：" << comboBox->currentText();
		}
		//与函数进行链接
		ui.btn_apply->disconnect();		//断开之前所有的连接
		connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
			QString str;
			str.append(currentText+'(');
			//遍历出当前页面所有QLineEdit的值	//根据QComboBox在页面中的布局， 最上面的是第一个，以此类推	//顺序和名字无关
			QList<QComboBox*> comboBoxList = ui.stackedWidget->currentWidget()->findChildren<QComboBox*>();
			for (int i = 0; i < comboBoxList.count(); ++i) {
				QComboBox* comboBox = comboBoxList.at(i);
				if(i==comboBoxList.count()-1) str.append(comboBox->currentText());
				else str.append(comboBox->currentText()+',');
				//qDebug() << "遍历所有：" << comboBox->currentText();
			}
			str.append(')');
			//qDebug() << str;
			//发送
			emit seedData(str);
		});
	}
	else{	
		qDebug() << "未查询到Map值！";
		ui.stackedWidget->setCurrentIndex(0);	
	}
	
}

//	
/*	链接：https://blog.csdn.net/weixin_44390515/article/details/117780144
 *	读取txt文件，并将读取到的信息加入QMap中
 *	txt格式为UTF-8，否则会乱码
 *	只读取txt文件中固定要求的信息：
		1、信息必须由制表符"\t"分割
		2、列数必须为4，否则不识别
 */
void operator_window::readTxt2Map(QString filePath, QMap<QString, operatorInfoStruct> &Map)
{
	//QString filePath = "F://Desktop//55.txt";
	//const char *filePath = "F://Desktop//55.txt";
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
			if (list.length() == 4) {	//只选取length = 4 的正确信息
				operatorInfoStruct infoStruct;
				infoStruct.currentIndex = list[1];
				infoStruct.title = list[2];
				infoStruct.intro = list[3];
				Map.insert(list[0], infoStruct);
				//将该函数名称加入comboBox中
				ui.comboBox->insertItem(ui.comboBox->count(), list[0]);
			}
		}
	}
	file.close();
}


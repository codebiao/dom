#include "operator_window.h"

operator_window::operator_window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//将该所有算子名称	FunctionName 加入comboBox中,插在末尾
	for (int i = 0; i < global_operatorInfoList.size(); ++i) {
		ui.comboBox->insertItem(ui.comboBox->count(), global_operatorInfoList.at(i).functionName);
	}

	//当算子combox 改变时调用selectAlgorithm函数， 并传入值
	connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(selectAlgorithm(QString)));
	//read_image页面中的“打开图片”图标，并将文件路径显示在comobox中
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(openImage()));
}

operator_window::~operator_window()
{
	qDebug("close operator_window");
}
//重写关闭函数
void operator_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------重写关闭函数------------";
	//this->hide();	 // 隐藏窗口
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // 忽视原来的关闭事件
}
//选择算子
void operator_window::selectAlgorithm(QString currentText) {
	qDebug() << "currentText="+ currentText;

	//按钮设为可点击
	ui.btn_apply->setEnabled(true);
	ui.btn_help->setEnabled(true);

	//根据当前Text查询Map表,取出结构体信息
	operatorInfoStruct operatorInfo;
	for (int i = 0; i < global_operatorInfoList.size(); ++i) {
		if (global_operatorInfoList[i].functionName == currentText) {
			operatorInfo = global_operatorInfoList[i];
			//qDebug() << "正在查找："+ global_operatorInfoList[i].functionName;
			break;
		};
	}
	qDebug() << "取出的结构体信息title=" + operatorInfo.title;
	ui.groupBox->setTitle(operatorInfo.title);
	qDebug() << "取出的结构体信息info=" + operatorInfo.intro;
	ui.introduce->setText(operatorInfo.intro);
	qDebug() << "取出的结构体信息currentIndex=" + operatorInfo.currentIndex;
	ui.stackedWidget->setCurrentIndex(operatorInfo.currentIndex.toInt());
		
	//与函数进行链接
	ui.btn_apply->disconnect();		//断开之前所有的连接
	connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
		QString str;
		str.append(currentText+'(');
		//遍历出当前页面所有QComboBox的值	//根据QComboBox在页面中的布局， 最上面的是第一个，以此类推	//顺序和名字无关
		QList<QComboBox*> comboBoxList = ui.stackedWidget->currentWidget()->findChildren<QComboBox*>();
		for (int i = 0; i < comboBoxList.count(); ++i) {
			QComboBox* comboBox = comboBoxList.at(i);
			if(i==comboBoxList.count()-1) str.append(comboBox->currentText());
			else str.append(comboBox->currentText()+',');
			qDebug() << "遍历所有comboBox：" << comboBox->currentText();
		}
		str.append(')');
		//qDebug() << str;
		//发送
		emit seedData(str);
	});
}

//read_image页面中的“打开图片”图标，并将文件路径显示在comobox中
void operator_window::openImage() {
	qDebug() << "openImage";
	QString OpenFile, OpenFilePath;
	QImage image;

	OpenFile = QFileDialog::getOpenFileName(this,
		"please choose an image file",
		"",
		"Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
	if (OpenFile != "")
	{
		//显示图片的路径
		QFileInfo OpenFileInfo = QFileInfo(OpenFile);
		OpenFilePath = OpenFileInfo.filePath();
		ui.comboBox_7->setCurrentText(OpenFilePath);
	}
	
}
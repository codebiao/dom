#include "operator_window.h"

operator_window::operator_window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//当下拉框内容改变时出发selectAlgorithm函数
	connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(selectAlgorithm(QString)));
	
}

operator_window::~operator_window()
{
	qDebug("close operator_window");
}


void operator_window::selectAlgorithm(QString currentText) {
	qDebug() << "currentText="+ currentText;
	//QString currentText = ui.comboBox->currentText();
	ui.btn_apply->setEnabled(true);
	ui.btn_help->setEnabled(true);

	if (currentText == "图像分割") {
		// 算子介绍
		QString title = "图像分割";
		QString intro = "基于边缘的图像分割算法,基于canny算子的 边缘检测";
		ui.groupBox->setTitle(title);
		ui.introduce->setText(intro);
		//切换QStackedWidget页面，展示不同的参数
		ui.stackedWidget->setCurrentIndex(2);
		//与函数进行链接
		ui.btn_apply->disconnect();		//断开之前所有的连接
		connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
			//获取组件的值
			QString funName = "image_segmentation";
			QString param1 = ui.image_image_segmentation_pic_1->text();
			QString param2 = ui.image_image_segmentation_outRegion->text();
			QString param3 = ui.image_segmentation_yuzhi->text();
			//组合起来
			//发送
			emit seedData(funName+"("+ param1 +","+ param2 +","+ param3+")");
		});
	}
	else if(currentText=="图像拼接"){
		// 算子介绍
		QString title = "图像拼接";
		QString intro = "图像拼接,交叉检查算法:将第二幅图像的每个关键点逐个与第一幅图像的全部关键点进行比较。只有两个方向上都匹配到了同一对特征点，才认为是一个有效的匹配对。将第二幅图像的每个关键点逐个与第一幅图像的全部关键点进行比较。只有两个方向上都匹配到了同一对特征点";
		ui.groupBox->setTitle(title);
		ui.introduce->setText(intro);
		//切换QStackedWidget页面，展示不同的参数
		ui.stackedWidget->setCurrentIndex(1);
		//与函数进行链接
		ui.btn_apply->disconnect();		//断开之前所有的连接
		connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
			
			emit seedData("图像拼接image_segmentation");

		});
	}
	else {
		qDebug() << "else";
	}
}




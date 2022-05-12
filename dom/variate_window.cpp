#include "variate_window.h"



variate_window::variate_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//创建布局
	flowLayout = new QFlowLayout(ui.scrollAreaWidgetContents);


	connect(ui.actionshauxin, SIGNAL(triggered()), this, SLOT(shuaxin()));
}

void variate_window::shuaxin() {
	//清空horizontalLayout布局内的所有元素
	QLayoutItem *child;
	while ((child = flowLayout->takeAt(0)) != 0)
	{
		//setParent为NULL，防止删除之后界面不消失
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}

		delete child;
	}
	
}
//重写关闭函数
void variate_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------重写关闭函数------------";
	//this->hide();	 // 隐藏窗口
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // 忽视原来的关闭事件
}
variate_window::~variate_window(){}

void variate_window::update() {
	//更新窗口
	qDebug() << "--------------变量窗口update函数------------";
	//清空horizontalLayout布局内的所有元素
	QLayoutItem *child;
	while ((child = flowLayout->takeAt(0)) != 0)
	{
		//setParent为NULL，防止删除之后界面不消失
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}
	
	//遍历QList,添加控件
	for (int i = 0; i < global_regionList.size(); ++i)
	{
		regionStruct regionStruct = global_regionList.at(i);
		qDebug() << regionStruct.regionName << "窗口被创建";
		Mat mat = regionStruct.regionMat;
		//创建QLabel
		VariateLabel *label = new VariateLabel(mat);	//通过构造函数传入Mat值，在VariateLabel类中定义signal
		label->resize(80, 80);
		//调用全局函数，将Mat显示在Label中
		global_matToQimageLabelShow(label, mat);
		QFrame * frame = new QFrame(this);
		//创建下标label
		QLabel *nameLabel = new QLabel(frame);
		nameLabel->setAlignment(Qt::AlignCenter);	//设置文字居中显示
		nameLabel->setText(regionStruct.regionName);
		//创建垂直布局依附于frame，将图片label和下标nameLabel添加到布局中
		QVBoxLayout *vy = new QVBoxLayout(frame);
		vy->addWidget(label);
		vy->addWidget(nameLabel);
		vy->setMargin(0);	//设置外边距	//vy->setSpacing(0);//设置内边距;
		//将fram添加到flowLayout布局中
		flowLayout->addWidget(frame);

		//将该label与本窗口中的槽函数进行链接//通过窗口利用【多重信号】进行中转
		connect(label, SIGNAL(clicked(Mat)), this, SLOT(LabelTrans2Window(Mat)));
	}

}
//只是个中转站
//Label里的signal，转到该槽函数中进行处理
void variate_window::LabelTrans2Window(Mat mat) {
	qDebug() << "--------------LabelTrans2Window函数------------";
	//将中转的数据发送出去， 在output窗口中显示
	//在主界面dom.cpp中进行connect
	emit sendMat2OutputWindow(mat);
}


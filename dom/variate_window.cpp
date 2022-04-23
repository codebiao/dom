#include "variate_window.h"



variate_window::variate_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//创建布局
	QScrollArea *scrollArea = ui.scrollArea;
	flowLayout = new QFlowLayout(scrollArea);

}

variate_window::~variate_window(){}

void variate_window::update() {
	//更新窗口
	qDebug() << "--------------变量窗口update函数------------";
	//先删除layout中所有的控件
	for (int i = 0; i < flowLayout->count(); i++)
	{
		QLayoutItem * item = flowLayout->itemAt(i);
		flowLayout->removeItem(item);
		//Debug() << "remove item " << i;
	}

	//遍历QMap,添加控件
	QMapIterator<QString, Mat> iterator(RegionMap);
	while (iterator.hasNext()) {
		iterator.next();
		qDebug() << iterator.key() << "窗口被创建";
		Mat mat = iterator.value();
		//创建QLabel
		VariateLabel *label = new VariateLabel(mat);	//通过构造函数传入Mat值，在VariateLabel类中定义signal
		label->resize(80, 80);
		//调用全局函数，将Mat显示在Label中
		global_matToQimageLabelShow(label, mat);
		//创建下标label
		QLabel *nameLabel = new QLabel(this);
		nameLabel->setAlignment(Qt::AlignCenter);	//设置文字居中显示
		nameLabel->setText(iterator.key());
		//创建垂直布局依附于frame，将图片label和下标nameLabel添加到布局中
		QFrame * frame = new QFrame(this);
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
	sendMat2OutputWindow(mat);
}


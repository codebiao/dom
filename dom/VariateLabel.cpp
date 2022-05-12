#include "VariateLabel.h"

VariateLabel::VariateLabel(QWidget *parent)
	: QLabel(parent){}

//重载构造函数
VariateLabel::VariateLabel(Mat mat) {
	this->mat = mat;
}

VariateLabel::~VariateLabel(){}

void VariateLabel::mousePressEvent(QMouseEvent *ev)
{
	//如果单击了就触发clicked信号
	if (ev->button() == Qt::LeftButton) {
	
		//触发clicked信号
		qDebug() <<"被电击了";
		emit clicked(this->mat);
	}
	//将该事件传给父类处理
	QLabel::mousePressEvent(ev);
}

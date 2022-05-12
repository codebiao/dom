#include "VariateLabel.h"

VariateLabel::VariateLabel(QWidget *parent)
	: QLabel(parent){}

//���ع��캯��
VariateLabel::VariateLabel(Mat mat) {
	this->mat = mat;
}

VariateLabel::~VariateLabel(){}

void VariateLabel::mousePressEvent(QMouseEvent *ev)
{
	//��������˾ʹ���clicked�ź�
	if (ev->button() == Qt::LeftButton) {
	
		//����clicked�ź�
		qDebug() <<"�������";
		emit clicked(this->mat);
	}
	//�����¼��������ദ��
	QLabel::mousePressEvent(ev);
}

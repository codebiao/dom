#include "variate_window.h"



variate_window::variate_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//��������
	QScrollArea *scrollArea = ui.scrollArea;
	flowLayout = new QFlowLayout(scrollArea);
}

variate_window::~variate_window(){}

void variate_window::update() {
	//���´���
	qDebug() << "--------------��������update����------------";
	//��ɾ��layout�����еĿؼ�
	for (int i = 0; i < flowLayout->count(); i++)
	{
		QLayoutItem * item = flowLayout->itemAt(i);
		flowLayout->removeItem(item);
		//Debug() << "remove item " << i;
	}

	//����QMap,��ӿؼ�
	QMapIterator<QString, Mat> iterator(RegionMap);
	while (iterator.hasNext()) {
		iterator.next();
		qDebug() << iterator.key() << "���ڱ�����";
		Mat mat = iterator.value();
		//����QLabel
		VariateLabel *label = new VariateLabel(mat);	//ͨ�����캯������Matֵ����VariateLabel���ж���signal
		label->setMinimumSize(100, 100);
		label->setMaximumSize(100, 100);
		//����ȫ�ֺ�������Mat��ʾ��Label��
		global_matToQimageLabelShow(label, mat);
		flowLayout->addWidget(label);
		//����label�뱾�����еĲۺ�����������//ͨ���������á������źš�������ת
		connect(label, SIGNAL(clicked(Mat)), this, SLOT(LabelTrans2Window(Mat)));
	}
}
//ֻ�Ǹ���תվ
//Label���signal��ת���òۺ����н��д���
void variate_window::LabelTrans2Window(Mat mat) {
	qDebug() << "--------------LabelTrans2Window����------------";
	//����ת�����ݷ��ͳ�ȥ�� ��output��������ʾ
	//��������dom.cpp�н���connect
	sendMat2OutputWindow(mat);
}


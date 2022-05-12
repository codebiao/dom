#include "variate_window.h"



variate_window::variate_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//��������
	flowLayout = new QFlowLayout(ui.scrollAreaWidgetContents);


	connect(ui.actionshauxin, SIGNAL(triggered()), this, SLOT(shuaxin()));
}

void variate_window::shuaxin() {
	//���horizontalLayout�����ڵ�����Ԫ��
	QLayoutItem *child;
	while ((child = flowLayout->takeAt(0)) != 0)
	{
		//setParentΪNULL����ֹɾ��֮����治��ʧ
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}

		delete child;
	}
	
}
//��д�رպ���
void variate_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------��д�رպ���------------";
	//this->hide();	 // ���ش���
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // ����ԭ���Ĺر��¼�
}
variate_window::~variate_window(){}

void variate_window::update() {
	//���´���
	qDebug() << "--------------��������update����------------";
	//���horizontalLayout�����ڵ�����Ԫ��
	QLayoutItem *child;
	while ((child = flowLayout->takeAt(0)) != 0)
	{
		//setParentΪNULL����ֹɾ��֮����治��ʧ
		if (child->widget())
		{
			child->widget()->setParent(NULL);
		}
		delete child;
	}
	
	//����QList,��ӿؼ�
	for (int i = 0; i < global_regionList.size(); ++i)
	{
		regionStruct regionStruct = global_regionList.at(i);
		qDebug() << regionStruct.regionName << "���ڱ�����";
		Mat mat = regionStruct.regionMat;
		//����QLabel
		VariateLabel *label = new VariateLabel(mat);	//ͨ�����캯������Matֵ����VariateLabel���ж���signal
		label->resize(80, 80);
		//����ȫ�ֺ�������Mat��ʾ��Label��
		global_matToQimageLabelShow(label, mat);
		QFrame * frame = new QFrame(this);
		//�����±�label
		QLabel *nameLabel = new QLabel(frame);
		nameLabel->setAlignment(Qt::AlignCenter);	//�������־�����ʾ
		nameLabel->setText(regionStruct.regionName);
		//������ֱ����������frame����ͼƬlabel���±�nameLabel��ӵ�������
		QVBoxLayout *vy = new QVBoxLayout(frame);
		vy->addWidget(label);
		vy->addWidget(nameLabel);
		vy->setMargin(0);	//������߾�	//vy->setSpacing(0);//�����ڱ߾�;
		//��fram��ӵ�flowLayout������
		flowLayout->addWidget(frame);

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
	emit sendMat2OutputWindow(mat);
}


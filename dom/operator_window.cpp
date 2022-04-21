#include "operator_window.h"

operator_window::operator_window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//�����������ݸı�ʱ����selectAlgorithm����
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

	if (currentText == "ͼ��ָ�") {
		// ���ӽ���
		QString title = "ͼ��ָ�";
		QString intro = "���ڱ�Ե��ͼ��ָ��㷨,����canny���ӵ� ��Ե���";
		ui.groupBox->setTitle(title);
		ui.introduce->setText(intro);
		//�л�QStackedWidgetҳ�棬չʾ��ͬ�Ĳ���
		ui.stackedWidget->setCurrentIndex(2);
		//�뺯����������
		ui.btn_apply->disconnect();		//�Ͽ�֮ǰ���е�����
		connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
			//��ȡ�����ֵ
			QString funName = "image_segmentation";
			QString param1 = ui.image_image_segmentation_pic_1->text();
			QString param2 = ui.image_image_segmentation_outRegion->text();
			QString param3 = ui.image_segmentation_yuzhi->text();
			//�������
			//����
			emit seedData(funName+"("+ param1 +","+ param2 +","+ param3+")");
		});
	}
	else if(currentText=="ͼ��ƴ��"){
		// ���ӽ���
		QString title = "ͼ��ƴ��";
		QString intro = "ͼ��ƴ��,�������㷨:���ڶ���ͼ���ÿ���ؼ���������һ��ͼ���ȫ���ؼ�����бȽϡ�ֻ�����������϶�ƥ�䵽��ͬһ�������㣬����Ϊ��һ����Ч��ƥ��ԡ����ڶ���ͼ���ÿ���ؼ���������һ��ͼ���ȫ���ؼ�����бȽϡ�ֻ�����������϶�ƥ�䵽��ͬһ��������";
		ui.groupBox->setTitle(title);
		ui.introduce->setText(intro);
		//�л�QStackedWidgetҳ�棬չʾ��ͬ�Ĳ���
		ui.stackedWidget->setCurrentIndex(1);
		//�뺯����������
		ui.btn_apply->disconnect();		//�Ͽ�֮ǰ���е�����
		connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
			
			emit seedData("ͼ��ƴ��image_segmentation");

		});
	}
	else {
		qDebug() << "else";
	}
}




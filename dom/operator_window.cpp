#include "operator_window.h"

operator_window::operator_window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//����������������	FunctionName ����comboBox��,����ĩβ
	for (int i = 0; i < global_operatorInfoList.size(); ++i) {
		ui.comboBox->insertItem(ui.comboBox->count(), global_operatorInfoList.at(i).functionName);
	}

	//������combox �ı�ʱ����selectAlgorithm������ ������ֵ
	connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(selectAlgorithm(QString)));
	//read_imageҳ���еġ���ͼƬ��ͼ�꣬�����ļ�·����ʾ��comobox��
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(openImage()));
}

operator_window::~operator_window()
{
	qDebug("close operator_window");
}
//��д�رպ���
void operator_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------��д�رպ���------------";
	//this->hide();	 // ���ش���
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // ����ԭ���Ĺر��¼�
}
//ѡ������
void operator_window::selectAlgorithm(QString currentText) {
	qDebug() << "currentText="+ currentText;

	//��ť��Ϊ�ɵ��
	ui.btn_apply->setEnabled(true);
	ui.btn_help->setEnabled(true);

	//���ݵ�ǰText��ѯMap��,ȡ���ṹ����Ϣ
	operatorInfoStruct operatorInfo;
	for (int i = 0; i < global_operatorInfoList.size(); ++i) {
		if (global_operatorInfoList[i].functionName == currentText) {
			operatorInfo = global_operatorInfoList[i];
			//qDebug() << "���ڲ��ң�"+ global_operatorInfoList[i].functionName;
			break;
		};
	}
	qDebug() << "ȡ���Ľṹ����Ϣtitle=" + operatorInfo.title;
	ui.groupBox->setTitle(operatorInfo.title);
	qDebug() << "ȡ���Ľṹ����Ϣinfo=" + operatorInfo.intro;
	ui.introduce->setText(operatorInfo.intro);
	qDebug() << "ȡ���Ľṹ����ϢcurrentIndex=" + operatorInfo.currentIndex;
	ui.stackedWidget->setCurrentIndex(operatorInfo.currentIndex.toInt());
		
	//�뺯����������
	ui.btn_apply->disconnect();		//�Ͽ�֮ǰ���е�����
	connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
		QString str;
		str.append(currentText+'(');
		//��������ǰҳ������QComboBox��ֵ	//����QComboBox��ҳ���еĲ��֣� ��������ǵ�һ�����Դ�����	//˳��������޹�
		QList<QComboBox*> comboBoxList = ui.stackedWidget->currentWidget()->findChildren<QComboBox*>();
		for (int i = 0; i < comboBoxList.count(); ++i) {
			QComboBox* comboBox = comboBoxList.at(i);
			if(i==comboBoxList.count()-1) str.append(comboBox->currentText());
			else str.append(comboBox->currentText()+',');
			qDebug() << "��������comboBox��" << comboBox->currentText();
		}
		str.append(')');
		//qDebug() << str;
		//����
		emit seedData(str);
	});
}

//read_imageҳ���еġ���ͼƬ��ͼ�꣬�����ļ�·����ʾ��comobox��
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
		//��ʾͼƬ��·��
		QFileInfo OpenFileInfo = QFileInfo(OpenFile);
		OpenFilePath = OpenFileInfo.filePath();
		ui.comboBox_7->setCurrentText(OpenFilePath);
	}
	
}
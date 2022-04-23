#include "operator_window.h"

operator_window::operator_window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//��ʼ������ȡ�ļ�����Map��//�������������뵽comBox��
	QString filePath = "resource/operatorInfo.txt";	//���ļ���dom.qrc�����
	readTxt2Map(filePath, operatorInfoMap);

	//�����������ݸı�ʱ����selectAlgorithm����
	connect(ui.comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(selectAlgorithm(QString)));
	
}

operator_window::~operator_window()
{
	qDebug("close operator_window");
}

//ѡ������
void operator_window::selectAlgorithm(QString currentText) {
	qDebug() << "currentText="+ currentText;

	//��ť��Ϊ�ɵ��
	ui.btn_apply->setEnabled(true);
	ui.btn_help->setEnabled(true);

	//���ݵ�ǰText��ѯMap��,ȡ���ṹ����Ϣ
	operatorInfoStruct operatorInfo = operatorInfoMap.value(currentText);
	if (operatorInfo.title != NULL) {	//QMapδ��ѯ����Ϣʱ������Ĭ��ֵ��QStringĬ��Ϊ null //һ�㲻��鲻��
		qDebug() << "ȡ���Ľṹ����Ϣtitle=" + operatorInfo.title;
		ui.groupBox->setTitle(operatorInfo.title);
		qDebug() << "ȡ���Ľṹ����Ϣinfo=" + operatorInfo.intro;
		ui.introduce->setText(operatorInfo.intro);
		qDebug() << "ȡ���Ľṹ����ϢcurrentIndex=" + operatorInfo.currentIndex;
		ui.stackedWidget->setCurrentIndex(operatorInfo.currentIndex.toInt());

		//��������ǰҳ������QLineEdit��ֵ	//����QComboBox��ҳ���еĲ��֣� ��������ǵ�һ�����Դ�����	//˳��������޹�
		QList<QComboBox*> comboBoxList = ui.stackedWidget->currentWidget()->findChildren<QComboBox*>();
		for (int i = 0; i < comboBoxList.count(); ++i) {
			QComboBox* comboBox = comboBoxList.at(i);
			qDebug() << "�������У�" << comboBox->currentText();
		}
		//�뺯����������
		ui.btn_apply->disconnect();		//�Ͽ�֮ǰ���е�����
		connect(ui.btn_apply, &QPushButton::clicked, this, [=]() {
			QString str;
			str.append(currentText+'(');
			//��������ǰҳ������QLineEdit��ֵ	//����QComboBox��ҳ���еĲ��֣� ��������ǵ�һ�����Դ�����	//˳��������޹�
			QList<QComboBox*> comboBoxList = ui.stackedWidget->currentWidget()->findChildren<QComboBox*>();
			for (int i = 0; i < comboBoxList.count(); ++i) {
				QComboBox* comboBox = comboBoxList.at(i);
				if(i==comboBoxList.count()-1) str.append(comboBox->currentText());
				else str.append(comboBox->currentText()+',');
				//qDebug() << "�������У�" << comboBox->currentText();
			}
			str.append(')');
			//qDebug() << str;
			//����
			emit seedData(str);
		});
	}
	else{	
		qDebug() << "δ��ѯ��Mapֵ��";
		ui.stackedWidget->setCurrentIndex(0);	
	}
	
}

//	
/*	���ӣ�https://blog.csdn.net/weixin_44390515/article/details/117780144
 *	��ȡtxt�ļ���������ȡ������Ϣ����QMap��
 *	txt��ʽΪUTF-8�����������
 *	ֻ��ȡtxt�ļ��й̶�Ҫ�����Ϣ��
		1����Ϣ�������Ʊ��"\t"�ָ�
		2����������Ϊ4������ʶ��
 */
void operator_window::readTxt2Map(QString filePath, QMap<QString, operatorInfoStruct> &Map)
{
	//QString filePath = "F://Desktop//55.txt";
	//const char *filePath = "F://Desktop//55.txt";
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Can't open the file!" << endl;
	}
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		QString str(line);
		QStringList list = str.split("\n", QString::SkipEmptyParts);
		if (list.length() != 0) {	//ȥ��һЩ���е���Ϣ
			list = list[0].split("\t", QString::SkipEmptyParts);
			//qDebug() << "list.length=" << list.length() << "		list=" << list << endl;
			if (list.length() == 4) {	//ֻѡȡlength = 4 ����ȷ��Ϣ
				operatorInfoStruct infoStruct;
				infoStruct.currentIndex = list[1];
				infoStruct.title = list[2];
				infoStruct.intro = list[3];
				Map.insert(list[0], infoStruct);
				//���ú������Ƽ���comboBox��
				ui.comboBox->insertItem(ui.comboBox->count(), list[0]);
			}
		}
	}
	file.close();
}


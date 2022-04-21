#include "input_window.h"
#include"operator_window.h"
#include"image_segmentation.h"

input_window::input_window(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//qDebug() <<"input_window= " + variateMap["a"];
	connect(ui.btn_run, SIGNAL(clicked()), this, SLOT(run()));
	
}

input_window::~input_window()
{
}

//��������Ϣ QString -> QStringList[ funName , param1, param2, ...]
QStringList input_window::getFunInfo(QString str)
{
	qDebug() << "--------------getFunInfo����------------";
	QStringList result;
	//qDebug() << "��ǰ�е�ֵΪ��" + str;
	QStringList list = str.split("(", QString::SkipEmptyParts);
	QString funName = list[0];	//��ú�����
	result.append(funName);
	qDebug() << "��������" << funName;
	QStringList list2 = list[1].split(")", QString::SkipEmptyParts);//(" param1, param2, param3, ...")
	QStringList list3 = list2[0].split(",");
	for (int i = 0; i < list3.count(); i++) {
		qDebug() << "����[" << i << "]=" << list3[i];
		result.append(list3[i]);	//��ò���
	}
	qDebug() << "result: "<<result;
	return result;
}

//����operator_window ���ݹ��������ݵĲۺ���
void input_window::receiveData(QString data)
{
	//qDebug() << "���ܵ������ǣ�" + data;
	ui.plainTextEdit->appendPlainText(data);

}


void input_window::run() {
	//��ʼ֮ǰ�����RegionMap
	clearRegionMap();
	//RegionMap.clear();
	//clearRegionMap();
	//qDebug() << "RegionMap.size="+ RegionMap.size();
	QTextDocument* doc = ui.plainTextEdit->document(); //�ı�����
	int cnt = doc->blockCount();//ÿ���س�����һ�� block�飬һ��
	for (int i = 0; i < cnt; i++)
	{
		QString str = doc->findBlockByNumber(i).text(); //�ı��е�һ��
		str.remove(QRegExp("\\s"));		//�Ƴ����пո�
		if (str == NULL) continue;//���û���ݵĻ�����������
		QStringList funInfo = getFunInfo(str);			//	����str����ú������Ͳ���
		//ͼ��ָ�			//0-������ 1-inRegion 2-outRegion
		if (funInfo[0] == "image_segmentation") {
			qDebug() << "--------------image_segmentation����------------";
			//��ȡͼƬ��Mat
			String image_1 = "F://Desktop//55.png";
			cv::Mat inregion = imread(image_1);
			//imshow("inregion", inregion);
			//ִ�к���
			Mat outRegion;								//���ڽ������Matֵ
			QString outRegionName = funInfo[2];			//����QMap��ֵ
			image_segmentation::segmentation_1(inregion, outRegion, funInfo[3].toInt());
			//******************������������RegionMap*****************8
			RegionMap.insert(outRegionName, outRegion);
			//imshow("outRegion", outRegion);
			//����regionVector
			//GlobalParam::map = {"imregion",inregion};
			//GlobalParam::regionVector.append({ "imregion",inregion });
			//qDebug() << "regionVector="<< GlobalParam::regionVector;

		}else if (funInfo[0]=="") {
			
		}
	}
	//������ִ����󣬷����źţ��ñ������ڸ��´���
	emit updateToVariate();
}


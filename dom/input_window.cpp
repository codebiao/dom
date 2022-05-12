#include "input_window.h"
#include"operator_window.h"


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
//��д�رպ���
void input_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------��д�رպ���------------";
	//this->hide();	 // ���ش���
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // ����ԭ���Ĺر��¼�
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
	//��ʼ֮ǰ�����global_regionList
	//for (int i = 0; i < global_regionList.size(); i++) {
	//	global_regionList.removeAt(i);
	//}
	global_regionList.clear();
	QTextDocument* doc = ui.plainTextEdit->document();	//�ı�����
	int cnt = doc->blockCount();						//ÿ���س�����һ�� block�飬һ��
	CodeFactory codeFactory;							//����������Դ����
	for (int i = 0; i < cnt; i++)
	{
	try
	{
		QString str = doc->findBlockByNumber(i).text(); //�ı��е�һ��
		str.remove(QRegExp("\\s"));						//�Ƴ����пո�
		if (str == NULL) continue;						//���û���ݵĻ�����������
		QStringList funInfo = getFunInfo(str);			//����str����ú������Ͳ���
		
		//����������QString -> const char *
		string stringName = funInfo[0].toStdString();
		const char * funName = stringName.c_str();

		//���� ������funInfo[0] �ҵ��ú�������ȡ�������������ĸ���
		int inputNum = 0, outputNum = 0;
		for (int i = 0; i < global_operatorInfoList.size(); i++) {
			if (global_operatorInfoList[i].functionName == funInfo[0]) {
				inputNum = global_operatorInfoList[i].inputLen.toInt();
				outputNum = global_operatorInfoList[i].outputLen.toInt();
				break;
			}
		}
		//���û�ҵ��������ò�ѭ��
		if (inputNum == 0 && outputNum == 0) continue;	
/*---------------------------- 0 input, 1 output ----read_image() ����-----------------------------------------*/
		else if (inputNum == 0 && outputNum == 1) {
			Mat out;
			QList<QString> qstringList;
			//����0�Ǻ�����������1�������;  �Ӳ���2��ʼȫ����qstringList
			for (int i = 2; i < funInfo.size(); i++) {
				qstringList.append(funInfo[i]);
			}
			//qstringList.append("F://Desktop//55.png");
			bool isSucce = QMetaObject::invokeMethod(
				&codeFactory, funName, Qt::DirectConnection,		//�����ö����ָ�롢 ������
				Q_RETURN_ARG(Mat, out),									//����ֵ���ͣ�����ֵ
				Q_ARG(QList<QString>, qstringList));					//��������,����;
			//******************������������RegionMap*****************8
			if (isSucce) {
				regionStruct regionStruct;
				regionStruct.regionName = funInfo[1];
				regionStruct.regionMat = out;
				global_regionList.append(regionStruct);
			}
		}
/*---------------------------- 1 input, 1 output ---------------------------------------------*/
		else if (inputNum == 1 && outputNum == 1) {
			Mat out;
			QList<QString> qstringList;
			//����0�Ǻ�����������1��������; ����2�������, �Ӳ���3��ʼȫ����qstringList
			for (int i = 3; i < funInfo.size(); i++) {
				qstringList.append(funInfo[i]);
			}
			Mat src;
			//��ȫ�ֺ���RegionMap���ҵ�Mat
			for(int i = 0; i < global_regionList.size(); i++) {
				if (global_regionList.at(i).regionName == funInfo[1]) {
					src = global_regionList.at(i).regionMat;
				}
			}
			bool isSucce = QMetaObject::invokeMethod(
				&codeFactory, funName, Qt::DirectConnection,		//�����ö����ָ�롢 ������
				Q_RETURN_ARG(Mat, out),										//����ֵ���ͣ�����ֵ
				Q_ARG(Mat, src),
				Q_ARG(QList<QString>, qstringList));					//��������,����;
			
			//******************������������RegionMap*****************8
			if (isSucce) {
			
				regionStruct regionStruct;
				regionStruct.regionName = funInfo[2];
				regionStruct.regionMat = out;
				global_regionList.append(regionStruct);
			}
		}
/*---------------------------- 2 input, 1 output ----ͼ��ƴ�� �Ⱥ���-----------------------------------------*/
		else if (inputNum == 2 && outputNum == 1) {
			Mat out;
			QList<QString> qstringList;
			//����0�Ǻ�����������1��������;����2��������; ����3�������;�Ӳ���4��ʼȫ����qstringList
			for (int i = 4; i < funInfo.size(); i++) {
				qstringList.append(funInfo[i]);
			}
			//��ȫ�ֺ���RegionMap���ҵ�Mat
			Mat src1, src2;
			for (int i = 0; i < global_regionList.size(); i++) {
				if (global_regionList.at(i).regionName == funInfo[1]) {
					src1 = global_regionList.at(i).regionMat;
				}
				else if (global_regionList.at(i).regionName == funInfo[2]) {
					src2 = global_regionList.at(i).regionMat;
				}
			}
			bool isSucce = QMetaObject::invokeMethod(
				&codeFactory, funName, Qt::DirectConnection,		//�����ö����ָ�롢 ������
				Q_RETURN_ARG(Mat, out),									//����ֵ���ͣ�����ֵ
				Q_ARG(Mat, src1),
				Q_ARG(Mat, src2),
				Q_ARG(QList<QString>, qstringList));					//��������,����;
			//******************������������RegionMap*****************8
			if (isSucce) {
				regionStruct regionStruct;
				regionStruct.regionName = funInfo[3];
				regionStruct.regionMat = out;
				global_regionList.append(regionStruct);
			}
		}
	}
	catch (const std::exception& e)
	{
		//qDebug() <<"�� "<<i+1<<" ����ִ�д���"<<e.what();
		QString exceptionData = "�� " + QString::number(i + 1)+" �к���ִ�д���" +"\n" +QString(e.what());
		emit sendException2Dom(exceptionData);
		break;
	}

	}
	//������ִ����󣬷����źţ��ñ������ڸ��´���
	emit updateToVariate();

}


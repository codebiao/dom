#include "dom.h"
#include"qmdiarea.h"
#include"qmdisubwindow.h"

dom::dom(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->move(250,70);

	//��ʼ������
	outputWindow = new output_window(this);			//ʵ���� �������
	ui.mdiArea->addSubWindow(outputWindow);
	inputWindow = new input_window(this);			//ʵ�������봰��
	ui.mdiArea->addSubWindow(inputWindow);
	operatorWindow = new operator_window(this);		//ʵ���� ���Ӵ���
	ui.mdiArea->addSubWindow(operatorWindow);
	variateWindow = new variate_window(this);		//ʵ���� ��������
	ui.mdiArea->addSubWindow(variateWindow);
	

	//���� �򿪵Ĵ��� �Ĵ�С����ȻĬ��Ϊ��С��
	foreach(QMdiSubWindow* s, ui.mdiArea->subWindowList()) {
		s->resize(640, 440);
	}
	//���Ӻ���
	//����ͼ
	connect(ui.operator_window_action, SIGNAL(triggered()), this, SLOT(open_operator_window()));
	connect(ui.input_window_action, SIGNAL(triggered()), this, SLOT(open_input_window()));
	connect(ui.output_window_action, SIGNAL(triggered()), this, SLOT(open_output_window()));
	connect(ui.variate_window_action, SIGNAL(triggered()), this, SLOT(open_variate_window()));
	//��������
	connect(ui.image_stitch_action, SIGNAL(triggered()), this, SLOT(image_stitch()));
	connect(ui.image_segmentation_action, SIGNAL(triggered()), this, SLOT(image_segmentation()));


	connect(ui.action_test, SIGNAL(triggered()), this, SLOT(test()));

	//���� �����Ӵ��ڡ�  -> ��input���ڡ�
	connect(operatorWindow, SIGNAL(seedData(QString)), inputWindow, SLOT(receiveData(QString)));
	//���� ��input���ڡ�  -> ���������ڡ�
	connect(inputWindow, SIGNAL(updateToVariate()), variateWindow, SLOT(update()));
	//���� ���������ڡ�  -> ��output���ڡ�
	connect(variateWindow, SIGNAL(sendMat2OutputWindow(Mat)), this->outputWindow, SLOT(showMat(Mat)));
	//���� ��input���ڡ�  -> ��dom���ڡ� //���ʹ�����Ϣ
	connect(inputWindow, SIGNAL(sendException2Dom(QString)), this, SLOT(receiveException(QString)));
}	

void dom::test()
{
	QStringList result;
	QString str = "image_segmentation(inRegion,outRegion,100)";
	qDebug() << "str=    "+ str;
	QStringList list = str.split("(",QString::SkipEmptyParts);
	QString funName = list[0];//������
	result.append(funName);
	qDebug() << "������=	" << funName;
	QStringList list2 = list[1].split(")",QString::SkipEmptyParts);
	qDebug() << "list2=	" << list2;
	QStringList list3 =list2[0].split(",");
	for (int i = 0; i < list3.count(); i++) {
		qDebug() << "list3["<< i << " ]=" <<  list3[i];
		result.append(list3[i]);
	}
	qDebug() << "result=	" << result;
	
}

//�õ�input���ڴ����Ĵ�����Ϣ
void dom::receiveException(QString exception)
{
	qDebug() << "�õ�input���ڴ����Ĵ�����Ϣ����"+ exception;
	//����������QString -> const char *
	string exception1 = exception.toStdString();
	const char * exception2 = exception1.c_str();
	QMessageBox::information(
		this,
		tr("������Ϣ"),
		tr(exception2));
}


//�� ���봰��
void dom::open_input_window() 
{
	/*
	if (!isOpen("���봰��")) {
		inputWindow = new input_window(this);		//ʵ�������봰��
		ui.mdiArea->addSubWindow(inputWindow);		//�����봰����ӽ�mdiArea
	}
	inputWindow->show();
	*/
	qDebug() << "open_input_window";
	inputWindow->showNormal();
}
//�� ���Ӵ���
void dom::open_operator_window()
{
	operatorWindow->showNormal();
}
//�� �������
void dom::open_output_window()
{
	outputWindow->showNormal();
}
//�� ��������
void dom::open_variate_window()
{
	variateWindow->showNormal();
}



//���������ؼ�������"Ӧ��"��ť��ͼ��Ԥ����--ͼ��ƴ�� ���ӣ�
void dom::image_stitch()
{
	//�� ���� ����
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");
	comboBox->setCurrentText("ͼ��ƴ��");
}

void dom::image_segmentation()
{
	//�� ���� ����
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");	
	comboBox->setCurrentText("ͼ��ָ�");
}


/*
 *	�жϴ����Ƿ��Ѿ���
 *	input:	[ windowTitle:���ڵı��� ]
 *	output:	[ boolֵ ]
*/
bool dom::isOpen(QString windowTitle)
{
	bool judge = false;
	foreach(QMdiSubWindow* s, ui.mdiArea->subWindowList()) {
		if (s->windowTitle() == windowTitle) {
			judge = true;
			qDebug() << windowTitle << "+ activite" << endl;
		}
		
	}
	return judge;
}


//��Mat����ת����Qimage
QImage dom::cvMat2QImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}
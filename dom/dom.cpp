#include "dom.h"
#include"qmdiarea.h"
#include"qmdisubwindow.h"

dom::dom(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->move(250,70);

	inputWindow = new input_window(this);
	//ui.mdiArea->addSubWindow(inputWindow);
	//ui.mdiArea->addSubWindow(inputWindow);
	// ����Ĭ�ϴ򿪴���
	open_output_window();
	open_input_window();
	open_operator_window();
	open_variate_window();

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
	connect(variateWindow, SIGNAL(sendMat2OutputWindow(Mat)), outputWindow, SLOT(showMat(Mat)));
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


//�� ���봰��
void dom::open_input_window()
{
	//if (!isOpen("���봰��")) {
	//	inputWindow = new input_window(this);		//ʵ�������봰��
	//	ui.mdiArea->addSubWindow(inputWindow);		//�����봰����ӽ�mdiArea
	//}
	
	inputWindow->show();
}
//�� ���Ӵ���
void dom::open_operator_window()
{
	if (!isOpen("���Ӵ���")) {
		operatorWindow = new operator_window(this);		//ʵ���� ���Ӵ���
		ui.mdiArea->addSubWindow(operatorWindow);		//�� ���Ӵ��� ��ӽ�mdiArea
	}

	operatorWindow->show();

}
//�� �������
void dom::open_output_window()
{
	if (!isOpen("�������")) {
		outputWindow = new output_window(this);			//ʵ���� �������
		ui.mdiArea->addSubWindow(outputWindow);			//�� ������� ��ӽ�mdiArea
	}

	outputWindow->show();
}
//�� ��������
void dom::open_variate_window()
{
	if (!isOpen("��������")) {
		variateWindow = new variate_window(this);			//ʵ���� �������
		ui.mdiArea->addSubWindow(variateWindow);			//�� ������� ��ӽ�mdiArea
	}

	variateWindow->show();
}



//���������ؼ�������"Ӧ��"��ť��ͼ��Ԥ����--ͼ��ƴ�� ���ӣ�
void dom::image_stitch()
{
	//�� ���� ����
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");
	comboBox->setCurrentText("ͼ��ƴ��");
}
/*
// �жϲ����Ϸ���ִ�к����������ͼ��Ԥ����--ͼ��ƴ�� ���ӣ�
void dom::image_stitch_handle() {

	//��������ڣ�������show
	open_output_window();		
	//�жϲ����Ƿ�Ϸ�
	QLineEdit * image_stitch_pic_1 = operatorWindow->findChild<QLineEdit *>("image_stitch_pic_1");
	QLineEdit * image_stitch_pic_2 = operatorWindow->findChild<QLineEdit *>("image_stitch_pic_2");
	//QString text_ = image_stitch_pic_1->text();
	if (image_stitch_pic_1->text() == NULL || image_stitch_pic_2->text() == NULL) {
		QMessageBox::information(NULL, "��ʾ", "����Ϊ�գ�");
	}
	else{
	String image_1 = image_stitch_pic_1->text().toStdString();
	String image_2 = image_stitch_pic_2->text().toStdString();
	
	//const char* image_1 = "F://Desktop//1.png";//��
	//const char* image_2 = "F://Desktop//2.png";//��
	Mat img = imread(image_1);	//��
	Mat img2 = imread(image_2);	//��
	//ִ�к��� + ���Mat����
	pre_processing * preProcessing = new pre_processing(this);	//ʵ��������
	Mat dst = preProcessing->imageStitch->stitch_2(img, img2);	//dstΪ�����ͼƬ
	//�����������ڣ��������ɺ��ͼƬ
	QPixmap pix = QPixmap::fromImage(cvMat2QImage(dst) );//��Mat����ת����QImage��ת����QPixmap
	QLabel * fin_pic = outputWindow->findChild<QLabel *>("fin_pic");//�ҵ���ť
	fin_pic->setScaledContents(true); 
	fin_pic->setPixmap(pix.scaled(fin_pic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));	//д��ͼƬ
	//Qt::KeepAspectRatio  
	}//else end
}
*/
void dom::image_segmentation()
{
	//�� ���� ����
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");	
	comboBox->setCurrentText("ͼ��ָ�");
}

/*
void dom::image_segmentation_handle()
{
	//qDebug() << "image_segmentation_handle";
	//��������ڣ�������show
	open_output_window();
	//�жϲ����Ƿ�Ϸ�
	QLineEdit * image_segmentation_yuzhi = operatorWindow->findChild<QLineEdit *>("image_segmentation_yuzhi");
	QLineEdit * image_image_segmentation_pic_1 = operatorWindow->findChild<QLineEdit *>("image_image_segmentation_pic_1");
	if (image_image_segmentation_pic_1->text() == NULL || image_segmentation_yuzhi->text() == NULL) {
		QMessageBox::information(NULL, "��ʾ", "����Ϊ�գ�");
	}
	else {
		int yuzhi = image_segmentation_yuzhi->text().toInt();	//��ֵ
		String image_1 = image_image_segmentation_pic_1->text().toStdString();
		
		qDebug() << "image_1= "<<image_image_segmentation_pic_1->text() <<endl;
		Mat img = imread(image_1);								//ͼƬ����
		//ִ�к��� + ���Mat����
		pre_processing * preProcessing = new pre_processing(this);	//ʵ��������
		Mat dst = preProcessing->imageSegmentation->segmentation_1(img, yuzhi);	//dstΪ�����ͼƬ
		//�����������ڣ��������ɺ��ͼƬ
		QPixmap pix = QPixmap::fromImage(cvMat2QImage(dst));//��Mat����ת����QImage��ת����QPixmap
		QLabel * fin_pic = outputWindow->findChild<QLabel *>("fin_pic");//�ҵ���ť
		fin_pic->setScaledContents(true);
		fin_pic->setPixmap(pix.scaled(fin_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));	//д��ͼƬ
	}
}
*/




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
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
	// 启动默认打开窗口
	open_output_window();
	open_input_window();
	open_operator_window();
	open_variate_window();

	//设置 打开的窗口 的大小，不然默认为最小化
	foreach(QMdiSubWindow* s, ui.mdiArea->subWindowList()) {
		s->resize(640, 440);
	}
	//连接函数
	//打开视图
	connect(ui.operator_window_action, SIGNAL(triggered()), this, SLOT(open_operator_window()));
	connect(ui.input_window_action, SIGNAL(triggered()), this, SLOT(open_input_window()));
	connect(ui.output_window_action, SIGNAL(triggered()), this, SLOT(open_output_window()));
	connect(ui.variate_window_action, SIGNAL(triggered()), this, SLOT(open_variate_window()));
	//各种算子
	connect(ui.image_stitch_action, SIGNAL(triggered()), this, SLOT(image_stitch()));
	connect(ui.image_segmentation_action, SIGNAL(triggered()), this, SLOT(image_segmentation()));


	connect(ui.action_test, SIGNAL(triggered()), this, SLOT(test()));

	//连接 【算子窗口】  -> 【input窗口】
	connect(operatorWindow, SIGNAL(seedData(QString)), inputWindow, SLOT(receiveData(QString)));
	//连接 【input窗口】  -> 【变量窗口】
	connect(inputWindow, SIGNAL(updateToVariate()), variateWindow, SLOT(update()));
	//连接 【变量窗口】  -> 【output窗口】
	connect(variateWindow, SIGNAL(sendMat2OutputWindow(Mat)), outputWindow, SLOT(showMat(Mat)));
}	

void dom::test()
{
	QStringList result;
	QString str = "image_segmentation(inRegion,outRegion,100)";
	qDebug() << "str=    "+ str;
	QStringList list = str.split("(",QString::SkipEmptyParts);
	QString funName = list[0];//函数名
	result.append(funName);
	qDebug() << "函数名=	" << funName;
	QStringList list2 = list[1].split(")",QString::SkipEmptyParts);
	qDebug() << "list2=	" << list2;
	QStringList list3 =list2[0].split(",");
	for (int i = 0; i < list3.count(); i++) {
		qDebug() << "list3["<< i << " ]=" <<  list3[i];
		result.append(list3[i]);
	}
	qDebug() << "result=	" << result;
	
}


//打开 输入窗口
void dom::open_input_window()
{
	//if (!isOpen("输入窗口")) {
	//	inputWindow = new input_window(this);		//实例化输入窗口
	//	ui.mdiArea->addSubWindow(inputWindow);		//将输入窗口添加进mdiArea
	//}
	
	inputWindow->show();
}
//打开 算子窗口
void dom::open_operator_window()
{
	if (!isOpen("算子窗口")) {
		operatorWindow = new operator_window(this);		//实例化 算子窗口
		ui.mdiArea->addSubWindow(operatorWindow);		//将 算子窗口 添加进mdiArea
	}

	operatorWindow->show();

}
//打开 输出窗口
void dom::open_output_window()
{
	if (!isOpen("输出窗口")) {
		outputWindow = new output_window(this);			//实例化 输出窗口
		ui.mdiArea->addSubWindow(outputWindow);			//将 输出窗口 添加进mdiArea
	}

	outputWindow->show();
}
//打开 变量窗口
void dom::open_variate_window()
{
	if (!isOpen("变量窗口")) {
		variateWindow = new variate_window(this);			//实例化 输出窗口
		ui.mdiArea->addSubWindow(variateWindow);			//将 输出窗口 添加进mdiArea
	}

	variateWindow->show();
}



//调出参数控件、链接"应用"按钮（图像预处理--图像拼接 算子）
void dom::image_stitch()
{
	//打开 算子 窗口
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");
	comboBox->setCurrentText("图像拼接");
}
/*
// 判断参数合法、执行函数、输出（图像预处理--图像拼接 算子）
void dom::image_stitch_handle() {

	//打开输出窗口，若打开则show
	open_output_window();		
	//判断参数是否合法
	QLineEdit * image_stitch_pic_1 = operatorWindow->findChild<QLineEdit *>("image_stitch_pic_1");
	QLineEdit * image_stitch_pic_2 = operatorWindow->findChild<QLineEdit *>("image_stitch_pic_2");
	//QString text_ = image_stitch_pic_1->text();
	if (image_stitch_pic_1->text() == NULL || image_stitch_pic_2->text() == NULL) {
		QMessageBox::information(NULL, "提示", "不能为空！");
	}
	else{
	String image_1 = image_stitch_pic_1->text().toStdString();
	String image_2 = image_stitch_pic_2->text().toStdString();
	
	//const char* image_1 = "F://Desktop//1.png";//左
	//const char* image_2 = "F://Desktop//2.png";//右
	Mat img = imread(image_1);	//左
	Mat img2 = imread(image_2);	//右
	//执行函数 + 输出Mat类型
	pre_processing * preProcessing = new pre_processing(this);	//实例化算子
	Mat dst = preProcessing->imageStitch->stitch_2(img, img2);	//dst为输出的图片
	//输出到输出窗口，加载生成后的图片
	QPixmap pix = QPixmap::fromImage(cvMat2QImage(dst) );//将Mat类型转化成QImage再转化成QPixmap
	QLabel * fin_pic = outputWindow->findChild<QLabel *>("fin_pic");//找到按钮
	fin_pic->setScaledContents(true); 
	fin_pic->setPixmap(pix.scaled(fin_pic->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));	//写入图片
	//Qt::KeepAspectRatio  
	}//else end
}
*/
void dom::image_segmentation()
{
	//打开 算子 窗口
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");	
	comboBox->setCurrentText("图像分割");
}

/*
void dom::image_segmentation_handle()
{
	//qDebug() << "image_segmentation_handle";
	//打开输出窗口，若打开则show
	open_output_window();
	//判断参数是否合法
	QLineEdit * image_segmentation_yuzhi = operatorWindow->findChild<QLineEdit *>("image_segmentation_yuzhi");
	QLineEdit * image_image_segmentation_pic_1 = operatorWindow->findChild<QLineEdit *>("image_image_segmentation_pic_1");
	if (image_image_segmentation_pic_1->text() == NULL || image_segmentation_yuzhi->text() == NULL) {
		QMessageBox::information(NULL, "提示", "不能为空！");
	}
	else {
		int yuzhi = image_segmentation_yuzhi->text().toInt();	//阈值
		String image_1 = image_image_segmentation_pic_1->text().toStdString();
		
		qDebug() << "image_1= "<<image_image_segmentation_pic_1->text() <<endl;
		Mat img = imread(image_1);								//图片参数
		//执行函数 + 输出Mat类型
		pre_processing * preProcessing = new pre_processing(this);	//实例化算子
		Mat dst = preProcessing->imageSegmentation->segmentation_1(img, yuzhi);	//dst为输出的图片
		//输出到输出窗口，加载生成后的图片
		QPixmap pix = QPixmap::fromImage(cvMat2QImage(dst));//将Mat类型转化成QImage再转化成QPixmap
		QLabel * fin_pic = outputWindow->findChild<QLabel *>("fin_pic");//找到按钮
		fin_pic->setScaledContents(true);
		fin_pic->setPixmap(pix.scaled(fin_pic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));	//写入图片
	}
}
*/




/*
 *	判断窗口是否已经打开
 *	input:	[ windowTitle:窗口的标题 ]
 *	output:	[ bool值 ]
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


//将Mat类型转化成Qimage
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
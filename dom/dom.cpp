#include "dom.h"
#include"qmdiarea.h"
#include"qmdisubwindow.h"

dom::dom(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	this->move(250,70);

	//初始化窗口
	outputWindow = new output_window(this);			//实例化 输出窗口
	ui.mdiArea->addSubWindow(outputWindow);
	inputWindow = new input_window(this);			//实例化输入窗口
	ui.mdiArea->addSubWindow(inputWindow);
	operatorWindow = new operator_window(this);		//实例化 算子窗口
	ui.mdiArea->addSubWindow(operatorWindow);
	variateWindow = new variate_window(this);		//实例化 变量窗口
	ui.mdiArea->addSubWindow(variateWindow);
	

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

	QList<QAction *>  actionList = ui.menu_2->actions();	//图像预处理
	QList<QAction *>  actionList2 = ui.menu_3->actions();	//特征处理
	QList<QAction *>  actionList3 = ui.menu_5->actions();	//蚕丝
	//合并所有QList
	actionList.append(actionList2);
	actionList.append(actionList3);
	//开始链接
	for (int i = 0; i < actionList.size(); i++) {
		QAction* action = actionList.at(i);
		connect(action, &QAction::triggered, this, [=]() {
			set_data2operator_comboBox(action->text());
		});
	}


	//连接 【算子窗口】  -> 【input窗口】
	connect(operatorWindow, SIGNAL(seedData(QString)), inputWindow, SLOT(receiveData(QString)));
	//连接 【input窗口】  -> 【变量窗口】
	connect(inputWindow, SIGNAL(updateToVariate()), variateWindow, SLOT(update()));
	//连接 【变量窗口】  -> 【output窗口】
	connect(variateWindow, SIGNAL(sendMat2OutputWindow(Mat)), this->outputWindow, SLOT(showMat(Mat)));
	//连接 【input窗口】  -> 【dom窗口】 //传送错误信息
	connect(inputWindow, SIGNAL(sendException2Dom(QString)), this, SLOT(receiveException(QString)));
}	

//拿到input窗口传来的错误信息
void dom::receiveException(QString exception)
{
	qDebug() << "拿到input窗口传来的错误信息！！"+ exception;
	//将函数名从QString -> const char *
	string exception1 = exception.toStdString();
	const char * exception2 = exception1.c_str();
	QMessageBox::information(
		this,
		tr("错误信息"),
		tr(exception2));
}

//打开 输入窗口
void dom::open_input_window() 
{
	/*
	if (!isOpen("输入窗口")) {
		inputWindow = new input_window(this);		//实例化输入窗口
		ui.mdiArea->addSubWindow(inputWindow);		//将输入窗口添加进mdiArea
	}
	inputWindow->show();
	*/
	qDebug() << "open_input_window";
	inputWindow->showNormal();
}
//打开 算子窗口
void dom::open_operator_window()
{
	operatorWindow->showNormal();
}
//打开 输出窗口
void dom::open_output_window()
{
	outputWindow->showNormal();
}
//打开 变量窗口
void dom::open_variate_window()
{
	variateWindow->showNormal();
}

//通过点击菜单中的【算子】，填入operatorWindow中的QComboBox中
void dom::set_data2operator_comboBox(QString str) {
	qDebug() << "qqqq";
	open_operator_window();
	QComboBox * comboBox = operatorWindow->findChild<QComboBox *>("comboBox");
	comboBox->setCurrentText(str);
}

/*
 *	判断窗口是否已经打开
 *	input:	[ windowTitle:窗口的标题 ]
 *	output:	[ bool值 ]

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
*/

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
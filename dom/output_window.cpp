#include "output_window.h"


output_window::output_window(QWidget *parent)
	: QMainWindow(parent)
{
	
	ui.setupUi(this);
}

output_window::~output_window()
{
}
void output_window::showMat(Mat mat) {
	qDebug() << "--------------showMat函数------------";
	//调用全局函数，将Mat显示在Label中
	global_matToQimageLabelShow(ui.label , mat);
}

//重写关闭函数
void output_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------重写关闭函数------------";
	//this->hide();	 // 隐藏窗口
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // 忽视原来的关闭事件

}
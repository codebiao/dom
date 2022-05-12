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
	qDebug() << "--------------showMat����------------";
	//����ȫ�ֺ�������Mat��ʾ��Label��
	global_matToQimageLabelShow(ui.label , mat);
}

//��д�رպ���
void output_window::closeEvent(QCloseEvent *e) {
	qDebug() << "--------------��д�رպ���------------";
	//this->hide();	 // ���ش���
	//this->setParent(nullptr);
	this->setWindowState(Qt::WindowMinimized);
	e->ignore(); // ����ԭ���Ĺر��¼�

}
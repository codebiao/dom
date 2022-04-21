#include "dom.h"
#include "input_window.h"
#include "variate_window.h"
#include "output_window.h"
#include <QtWidgets/QApplication>
#include <QVector>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
	dom w;
	w.setWindowTitle("dom主窗体"); // 此处写应用程序在标题栏上显示的名称
    w.show();
    return a.exec();
}

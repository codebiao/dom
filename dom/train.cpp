#include "train.h"

train::train(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.start, SIGNAL(clicked()), this, SLOT(test()));



}

train::~train()
{}

void train::test() {
	qDebug() << "train::test()" ;
	//在此调用python代码
	






}

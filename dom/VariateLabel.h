#pragma once
#pragma execution_character_set("utf-8")
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include<qdebug.h>
#include"GlobalParam.h"

class VariateLabel : public QLabel
{
	Q_OBJECT

public:
	VariateLabel(QWidget *parent = nullptr);
	~VariateLabel();
	//���ع��캯��
	VariateLabel(Mat mat);
signals:
	void clicked(Mat);
protected:
	virtual void mousePressEvent(QMouseEvent* event); //��дmousePressEvent�¼�
public:
	Mat mat;
};

#pragma once

#include <QObject>
#include"image_stitch.h"
#include"image_segmentation.h"
#include<QDebug>

class pre_processing : public QObject
{
	Q_OBJECT

public:
	pre_processing(QObject *parent);
	~pre_processing();

	//ͼ��ƴ�� ��ʵ����
	image_stitch * imageStitch;
	//ͼ��ָ� ��ʵ����
	image_segmentation * imageSegmentation;

};

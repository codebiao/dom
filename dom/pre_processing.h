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

	//图像拼接 的实体类
	image_stitch * imageStitch;
	//图像分割 的实体类
	image_segmentation * imageSegmentation;

};

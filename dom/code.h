#pragma once

#include <QObject>
#include"pre_processing.h"

class code : public QObject
{
	Q_OBJECT

public:
	code(QObject *parent);
	~code();
	pre_processing* preProcessing;			// ‘§¥¶¿Ì
};

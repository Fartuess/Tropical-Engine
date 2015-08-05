#pragma once

#include <QtCore/qlist.h>
#include "Model/Model.h"

class AbstractModelImporter
{
public:
	AbstractModelImporter();
	~AbstractModelImporter();

	virtual Model* Load(QString name, QString fileUrl) = 0;

	QList<QString> getSupportedExtensions();

protected:
	QList<QString> supportedExtensions;
};


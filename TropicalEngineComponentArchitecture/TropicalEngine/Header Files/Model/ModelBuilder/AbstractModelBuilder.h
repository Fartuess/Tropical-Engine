#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

class AbstractModelBuilder
{
protected:
	QString modelType;
	QMap<QString, void*> parameters;
public:

	AbstractModelBuilder();
	~AbstractModelBuilder();

	QString getModelType();
	void setParameter(QString name, void* value);
	virtual class Model* Build() = 0;
	virtual void resetParameters();
};


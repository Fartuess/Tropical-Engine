#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

class Model;
class ModelBuilder;

class ModelManager
{
public:
	friend class ModelComponent;
	friend class ModelBuilder;

	ModelManager(void);
	~ModelManager(void);

	Model* getModel(QString name);

	void Load(QString fileUrl, QString name);
	void Load(Model* model, QString name);

private:
	QMap<QString, Model*> models;

	void FlushModel(QString name, bool forced = false);
};


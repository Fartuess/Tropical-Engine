#pragma once
#include "singleton.h"
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class Model;
class ModelBuilder;

class ModelManager :
	public Singleton<ModelManager>
{
public:
	friend class ModelComponent;
	friend class ModelBuilder;
private:
	QMap<QString, Model*> models;
public:
	ModelManager(void);
	~ModelManager(void);

	void Load(QString fileUrl, QString name);
private:
	void Load(Model* model, QString name);
	void FlushModel(QString name, bool forced = false);
};


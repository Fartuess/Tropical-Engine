#pragma once
#include "ModelComponent.h"
#include "singleton.h"
#include <QtCore\qstring.h>
#include <QtCore\qlist.h>
#include <QtCore\qmap.h>

class CameraComponent;

class ModelManager :
	public Singleton<ModelManager>
{
public:
	friend class ModelComponent;
	friend class Material;
	friend class MaterialManager;
private:
	QMap<QString, Model*> models;
	QList<ModelComponent*> modelComponents;
public:
	ModelManager(void);
	~ModelManager(void);

	void Load(QString fileUrl, QString name);
	void Load(Model* model, QString name);
private:
	void FlushModel(QString name, bool forced = false);
	void DropComponent(ModelComponent* component);
public:
	void DrawAll(CameraComponent* viewer);
};


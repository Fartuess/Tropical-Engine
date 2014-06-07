#pragma once
#include <QtCore\qlist.h>
#include "singleton.h"

class CameraComponent;
class ModelComponent;

class ModelController// :
	//public Singleton<ModelController>
{
public:
	friend class ModelComponent;
	friend class Material;
	friend class MaterialManager;
private:
	QList<ModelComponent*> modelComponents;
public:
	ModelController(void);
	~ModelController(void);
	void AddComponent(ModelComponent* component);
private:
	void DropComponent(ModelComponent* component);
public:
	void DrawAll(CameraComponent* viewer);
};


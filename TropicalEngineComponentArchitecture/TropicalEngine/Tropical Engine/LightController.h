#pragma once
#include "LightComponent.h"
#include "singleton.h"
#include <QtCore\qlist.h>

class ModelComponent;

class LightController// :
	//public Singleton<LightController>
{
public:
	friend class LightComponent;
private:
	QList<LightComponent*> lights;
	QList<ModelComponent*> shadowcasters;
public:
	LightController(void);
	~LightController(void);

	QList<LightComponent*> getLights();	//should it return static reference?
	QList<ModelComponent*> getShadowcasters();
private:
	void DropComponent(LightComponent* component);
public:
	void EvaluateAll();
	//void EvaluateShadowsAll();
};


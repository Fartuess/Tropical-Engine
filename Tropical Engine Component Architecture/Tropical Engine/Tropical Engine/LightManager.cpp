#include "LightManager.h"


LightManager::LightManager(void)
{
}


LightManager::~LightManager(void)
{
	foreach (LightComponent* lightComponent, lights)
	{
		delete lightComponent;
	}
}

QList<LightComponent*> LightManager::getLights()
{
	return lights;
}

QList<ModelComponent*> LightManager::getShadowcasters()
{
	return shadowcasters;
}

void LightManager::DropComponent(LightComponent* component)
{
	delete component;
}

void LightManager::EvaluateAll()
{
	foreach (LightComponent* light, lights)
	{
		light->Evaluate();
	}
}

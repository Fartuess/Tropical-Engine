#include "LightController.h"


LightController::LightController(void)
{
}


LightController::~LightController(void)
{
	foreach (LightComponent* lightComponent, lights)
	{
		delete lightComponent;
	}
}

QList<LightComponent*> LightController::getLights()
{
	return lights;
}

QList<ModelComponent*> LightController::getShadowcasters()
{
	return shadowcasters;
}

void LightController::DropComponent(LightComponent* component)
{
	delete component;
}

void LightController::EvaluateAll()
{
	foreach (LightComponent* light, lights)
	{
		light->Evaluate();
	}
}

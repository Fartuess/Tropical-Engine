#include <Light/LightController.h>

namespace TropicalEngine
{

	LightController::LightController(void)
	{
		// TODO: implement it.
	}

	LightController::~LightController(void)
	{
		for (LightComponent* lightComponent : lights)
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
		for (LightComponent* light : lights)
		{
			light->Evaluate();
		}
	}

	void LightController::EvaluateShadowsAll()
	{
		for (LightComponent* light : lightShadows)
		{

		}
	}

}
#pragma once
#include <QtCore/qlist.h>

#include "LightComponent.h"

namespace TropicalEngine
{

	class ModelComponent;

	class LightController
	{
	public:
		friend class LightComponent;

		LightController(void);
		~LightController(void);

		QList<LightComponent*> getLights();	//should it return static reference?
		QList<ModelComponent*> getShadowcasters();

		void EvaluateAll();
		void EvaluateShadowsAll();

	private:
		QList<LightComponent*> lights;
		QList<LightComponent*> lightShadows;
		QList<ModelComponent*> shadowcasters;

		void DropComponent(LightComponent* component);
	};

}
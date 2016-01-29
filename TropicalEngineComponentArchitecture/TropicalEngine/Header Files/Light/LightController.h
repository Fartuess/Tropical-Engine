#pragma once
#include <QtCore/qlist.h>

#include "LightComponent.h"

namespace TropicalEngine
{

	// TODO: Split light information to separate scenes.
	// TODO: Finish documenting LightCpomponent class.
	#pragma region documentation
	/**
	  * \brief Class managing lights.
	  */
	#pragma endregion
	class LightController
	{
	public:
		friend class LightComponent;

		#pragma region documentation
		/**
		  * \brief LightController constructor.
		  */
		#pragma endregion
		LightController(void);
		#pragma region documentation
		/**
		  * \brief LightController destructor.
		  */
		#pragma endregion
		~LightController(void);

		#pragma region documentation
		/**
		  * \brief Gets list of lights.
		  *
		  * @return List of LightComponents.
		  */
		#pragma endregion
		QList<LightComponent*> getLights();	//should it return static reference?
		// TODO: Changer getShadowcasters method to return RenderComponents or even IRenderables.
		#pragma region documentation
		/**
		  * \brief Gets list of objects casting shadows.
		  *
		  * @return List of objects casting shadows.
		  */
		#pragma endregion
		QList<class ModelComponent*> getShadowcasters();

		void EvaluateAll();
		void EvaluateShadowsAll();

	private:
		QList<LightComponent*> lights;
		QList<LightComponent*> lightShadows;
		QList<class ModelComponent*> shadowcasters;

		void DropComponent(LightComponent* component);
	};

}
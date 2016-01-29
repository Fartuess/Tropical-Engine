#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for generating cylinder models.
	  *
	  * Parameters are:
	  * radius (float)
	  * height (float)
	  * subdivisions axis (int)
	  * subdivisions height (int)
	  */
	#pragma endregion
	class CylinderModelBuilder : public AbstractModelBuilder
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		CylinderModelBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~CylinderModelBuilder();

		#pragma region documentation
		/**
		  * \brief Resets values of parameters.
		  */
		#pragma endregion
		void resetParameters() override;

		#pragma region documentation
		/**
		  * \brief Creates model using set parameters.
		  *
		  * Creates model using set parameters and adds it to model manager.
		  * @return Generated model.
		  */
		#pragma endregion
		class Model* Build() override;
	};

}
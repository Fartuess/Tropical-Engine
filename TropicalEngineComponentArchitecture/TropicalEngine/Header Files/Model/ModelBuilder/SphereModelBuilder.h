#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for generating sphere models.
	  *
	  * Parameters are:
	  * radius (float)
	  * subdivisions axis (int)
	  * subdivisions height (int)
	  */
	#pragma endregion
	class SphereModelBuilder : public AbstractModelBuilder
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		SphereModelBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~SphereModelBuilder();

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
#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for generating torus models.
	  *
	  * Parameters are:
	  * radius (float)
	  * section radius (float)
	  * subdivisions axis (int)
	  * subdivisions height (int)
	  */
	#pragma endregion
	class TorusModelBuilder : public AbstractModelBuilder
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		TorusModelBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~TorusModelBuilder();

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
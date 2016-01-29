#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for generating plane models.
	  *
	  * Parameters are:
	  * size X (float)
	  * size Y (float)
	  * subdivisions X (int)
	  * subdivisions Y (int)
	  * plane (PlaneDirections)
	  * inversed (bool)
	  * centered (bool)
	  */
	#pragma endregion
	class PlaneModelBuilder : public AbstractModelBuilder
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		PlaneModelBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~PlaneModelBuilder();

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
#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for generating box models.
	  *
	  * Parameters are:
	  * size X (float)
	  * size Y (float)
	  * size Z (float)
	  * subdivisions X (int)
	  * subdivisions Y (int)
	  * subdivisions Z (int)
	  */
	#pragma endregion
	class BoxModelBuilder : public AbstractModelBuilder
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		BoxModelBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~BoxModelBuilder();

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
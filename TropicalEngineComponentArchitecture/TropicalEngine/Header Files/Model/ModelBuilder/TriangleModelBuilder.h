#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for generating triangle models.
	  */
	#pragma endregion
	class TriangleModelBuilder : public AbstractModelBuilder
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		TriangleModelBuilder();
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~TriangleModelBuilder();

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
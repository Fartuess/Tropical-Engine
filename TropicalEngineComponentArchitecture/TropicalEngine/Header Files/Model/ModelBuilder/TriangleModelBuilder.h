#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	/**
	  * Class for generating triangle models.
	  */
	class TriangleModelBuilder : public AbstractModelBuilder
	{
	public:

		/**
		  * \brief Default constructor.
		  */
		TriangleModelBuilder();

		/**
		  * \brief Default destructor.
		  */
		~TriangleModelBuilder();

		/**
		  * \brief Creates model using set parameters.
		  *
		  * Creates model using set parameters and adds it to model manager.
		  * @return Generated model.
		  */
		class Model* Build() override;
	};

}
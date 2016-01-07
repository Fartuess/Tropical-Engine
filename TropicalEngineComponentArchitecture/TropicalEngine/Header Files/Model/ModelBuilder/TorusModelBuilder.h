#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	/**
	  * Class for generating torus models.
	  */
	class TorusModelBuilder : public AbstractModelBuilder
	{
	public:

		/**
		  * \brief Default constructor.
		  */
		TorusModelBuilder();

		/**
		  * \brief Default destructor.
		  */
		~TorusModelBuilder();

		/**
		  * \brief Resets values of parameters.
		  */
		void resetParameters() override;

		/**
		  * \brief Creates model using set parameters.
		  *
		  * Creates model using set parameters and adds it to model manager.
		  * @return Generated model.
		  */
		class Model* Build() override;
	};

}
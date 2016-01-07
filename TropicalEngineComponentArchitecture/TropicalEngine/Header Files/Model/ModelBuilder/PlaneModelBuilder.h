#pragma once
#include "AbstractModelBuilder.h"

namespace TropicalEngine
{

	/**
	  * Class for generating plane models.
	  */
	class PlaneModelBuilder : public AbstractModelBuilder
	{
	public:

		/**
		  * \brief Default constructor.
		  */
		PlaneModelBuilder();

		/**
		  * \brief Default destructor.
		  */
		~PlaneModelBuilder();

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
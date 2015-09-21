#pragma once
#include "AbstractModelBuilder.h"

/**
  * Class for generating sphere models.
  */
class SphereModelBuilder : public AbstractModelBuilder
{
public:

	/**
	  * \brief Default constructor.
	  */
	SphereModelBuilder();

	/**
	  * \brief Default destructor.
	  */
	~SphereModelBuilder();

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


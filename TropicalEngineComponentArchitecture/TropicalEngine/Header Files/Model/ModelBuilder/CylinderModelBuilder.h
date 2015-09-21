#pragma once
#include "AbstractModelBuilder.h"

/**
  * Class for generating cylinder models.
  */
class CylinderModelBuilder : public AbstractModelBuilder
{
public:

	/**
	  * \brief Default constructor.
	  */
	CylinderModelBuilder();

	/**
	  * \brief Default destructor.
	  */
	~CylinderModelBuilder();

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


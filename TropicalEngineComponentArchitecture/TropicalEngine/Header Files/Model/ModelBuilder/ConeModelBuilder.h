#pragma once
#include "AbstractModelBuilder.h"

/**
  * Class for generating cone models.
  */
class ConeModelBuilder : public AbstractModelBuilder
{
public:

	/**
	  * \brief Default constructor.
	  */
	ConeModelBuilder();

	/**
	  * \brief Default destructor.
	  */
	~ConeModelBuilder();

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


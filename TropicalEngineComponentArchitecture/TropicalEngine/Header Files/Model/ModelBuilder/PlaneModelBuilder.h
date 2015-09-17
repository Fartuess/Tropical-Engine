#pragma once
#include "AbstractModelBuilder.h"

class PlaneModelBuilder : public AbstractModelBuilder
{
public:
	PlaneModelBuilder();
	~PlaneModelBuilder();

	void resetParameters() override;
	class Model* Build() override;
};


#pragma once
#include "AbstractModelBuilder.h"

class SphereModelBuilder : public AbstractModelBuilder
{
public:
	SphereModelBuilder();
	~SphereModelBuilder();

	void resetParameters() override;
	class Model* Build() override;
};


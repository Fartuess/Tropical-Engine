#pragma once
#include "AbstractModelBuilder.h"

class TorusModelBuilder : public AbstractModelBuilder
{
public:
	TorusModelBuilder();
	~TorusModelBuilder();

	void resetParameters() override;
	class Model* Build() override;
};


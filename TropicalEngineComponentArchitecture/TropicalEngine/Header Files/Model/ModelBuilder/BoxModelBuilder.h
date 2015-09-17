#pragma once
#include "AbstractModelBuilder.h"

class BoxModelBuilder : public AbstractModelBuilder
{
public:
	BoxModelBuilder();
	~BoxModelBuilder();

	void resetParameters() override;
	class Model* Build() override;
};


#pragma once
#include "AbstractModelBuilder.h"

class TriangleModelBuilder : public AbstractModelBuilder
{
public:
	TriangleModelBuilder();
	~TriangleModelBuilder();

	class Model* Build() override;
};


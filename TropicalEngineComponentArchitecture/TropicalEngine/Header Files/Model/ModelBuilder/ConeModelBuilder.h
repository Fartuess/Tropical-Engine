#pragma once
#include "AbstractModelBuilder.h"

class ConeModelBuilder : public AbstractModelBuilder
{
public:
	ConeModelBuilder();
	~ConeModelBuilder();

	void resetParameters() override;
	class Model* Build() override;
};


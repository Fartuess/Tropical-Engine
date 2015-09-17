#pragma once
#include "AbstractModelBuilder.h"

class CylinderModelBuilder : public AbstractModelBuilder
{
public:
	CylinderModelBuilder();
	~CylinderModelBuilder();

	void resetParameters() override;
	class Model* Build() override;
};


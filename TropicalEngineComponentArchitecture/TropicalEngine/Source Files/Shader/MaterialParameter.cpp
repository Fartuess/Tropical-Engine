#include <Shader/MaterialParameter.h>

namespace TropicalEngine
{

	MaterialParameter::MaterialParameter()
	{
	}


	MaterialParameter::~MaterialParameter()
	{
	}

	MaterialParameter& MaterialParameter::operator=(void* data)
	{
		this->data = data;
		return *this;
	}

	void* MaterialParameter::operator*()
	{
		return data;
	}

}
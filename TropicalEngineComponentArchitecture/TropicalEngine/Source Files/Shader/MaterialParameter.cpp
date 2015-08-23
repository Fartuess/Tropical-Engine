#include <Shader/MaterialParameter.h>


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
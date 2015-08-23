#pragma once

///TODO: figure out if additional level of abstraction is usefull
class MaterialParameter
{
public:
	void* data;

	MaterialParameter();
	~MaterialParameter();

	MaterialParameter& operator=(void* data);
	void* operator*();
};


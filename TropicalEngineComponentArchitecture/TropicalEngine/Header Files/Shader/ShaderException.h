#pragma once

#include <Utills/Exception.h>

class ShaderException : public Exception<class Shader>
{
public:
	ShaderException(QString message, class Shader* shader);
	~ShaderException();
};


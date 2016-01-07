#include <Shader/ShaderException.h>

namespace TropicalEngine
{

	ShaderException::ShaderException(QString message, Shader* shader) : Exception(message, shader)
	{
	}


	ShaderException::~ShaderException()
	{
	}

}
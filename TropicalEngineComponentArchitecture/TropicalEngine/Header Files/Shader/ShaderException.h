#pragma once

#include <Utills/Exception.h>

namespace TropicalEngine
{

	/// TODO: Figure out if its even needed.
	class ShaderException : public Exception<class Shader>
	{
	public:
		ShaderException(QString message, class Shader* shader);
		~ShaderException();
	};

}
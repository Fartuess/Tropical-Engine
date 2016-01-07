#include <Shader/ShaderBuilder/AbstractShaderBuilder.h>

namespace TropicalEngine
{

	AbstractShaderBuilder::AbstractShaderBuilder()
	{
	}


	AbstractShaderBuilder::~AbstractShaderBuilder()
	{
	}

	void AbstractShaderBuilder::setInput(QString name, QString path)
	{
		if (inputs.contains(name))
		{
			inputs[name] = path;
		}
	}

}
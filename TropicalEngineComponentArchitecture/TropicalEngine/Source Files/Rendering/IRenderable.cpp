#include <Rendering/IRenderable.h>

namespace TropicalEngine
{
	bool IRenderable::hasShaderPass(QString shaderPass)
	{
		return getShaderPasses().contains(shaderPass);
	}
}
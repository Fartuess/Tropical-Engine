#include <Shader/Shader.h>
#include <Shader/ShaderBuilder/AbstractShaderBuilder.h>
#include <Shader/ShaderManager.h>

#include <Shader/ShaderTechnique.h>

#include <TropicalEngineApplication.h>

namespace TropicalEngine
{

	ShaderTechnique::ShaderTechnique(QString name, AbstractShaderBuilder* shaderBuilder, bool managed)
	{
		this->name = name;

		this->shaderBuilder = shaderBuilder;

		this->isManaged = managed;
	}


	ShaderTechnique::~ShaderTechnique()
	{
	}

	void ShaderTechnique::setInput(QString name, QString path)
	{
		shaderBuilder->setInput(name, path);
	}

	//void ShaderTechnique::addShaderPass(QString name, class Shader* shader)
	//{
	//	if (!(shaderPasses.contains(name)))
	//	{
	//		shaderPasses[name] = shader;
	//	}
	//}

	Shader* ShaderTechnique::getShader(QString shaderPass)
	{
		/// TODO: This can screw up if same shader builder was used with different inputs.

		if (!shaderPasses.contains(shaderPass))
		{
			generateShader(shaderPass);
		}
		return shaderPasses[shaderPass];
	}

	class Shader* ShaderTechnique::generateShader(QString shaderPass)
	{
		shaderPasses[shaderPass] = shaderBuilder->createShader(name, shaderPass);

		if (isManaged)
		{
			TropicalEngineApplication::instance()->shaderManager->Load(shaderPasses[shaderPass], shaderPasses[shaderPass]->getName());
		}

		return shaderPasses[shaderPass];
	}

	//class Shader* generateShaders()
	//{
	//
	//}

}
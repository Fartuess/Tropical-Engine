#include <gl/glew.h>

#include <Shader/Shader.h>
#include <Shader/ShaderTechnique.h>
#include <Shader/ShaderManager.h>

namespace TropicalEngine
{

	ShaderManager::ShaderManager(void)
	{
	}

	ShaderManager::~ShaderManager(void)
	{
		for (Shader* shader : shaders)
		{
			delete shader;
		}
	}

	Shader* const ShaderManager::getCurrentShader()
	{
		return currentShader;
	}

	void ShaderManager::setCurrentShader(Shader* shader)
	{
		currentShader = shader;
	}

	Shader* const ShaderManager::getShader(QString name)
	{
		return shaders[name];
	}

	ShaderTechnique* ShaderManager::getShaderTechnique(QString name)
	{
		return shaderTechniques[name];
	}

	void ShaderManager::FlushShader(QString name)
	{
		///TODO: implement it.
	}

	void ShaderManager::Load(Shader* shader, QString name)
	{
		shaders[name] = shader;
	}

	Shader* ShaderManager::Load(QString name, QString vertexShader, QString fragmentShader)
	{
		Shader* newShader = new Shader(name);
		newShader->AddShader(vertexShader, GL_VERTEX_SHADER);
		newShader->AddShader(fragmentShader, GL_FRAGMENT_SHADER);
		newShader->FinalizeShader();

		shaders[name] = newShader;

		return newShader;
	}

	void ShaderManager::Load(class ShaderTechnique* shader, QString name)
	{
		shaderTechniques[name] = shader;
	}

	void ShaderManager::UseShader(QString name)
	{
		shaders[name]->Use();
	}

	void ShaderManager::UseShader(Shader* shader)
	{
		shader->Use();
	}
}
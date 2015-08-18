#include <gl/glew.h>

#include <Shader/Shader.h>
#include <Shader/ShaderManager.h>

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

Shader* ShaderManager::getCurrentShader()
{
	return currentShader;
}

void ShaderManager::setCurrentShader(Shader* shader)
{
	currentShader = shader;
}

void ShaderManager::FlushShader(QString name)
{
	///TODO: implement it.
}

void ShaderManager::Load(Shader* shader, QString name)
{
	shaders.insert(name, shader);
}

void ShaderManager::Load(QString vertexShader, QString fragmentShader, QString name)
{
	shaders.insert(name, new Shader(vertexShader, fragmentShader, name));
}

void ShaderManager::UseShader(QString name)
{
	shaders[name]->Use();
}

void ShaderManager::UseShader(Shader* shader)
{
	shader->Use();
}
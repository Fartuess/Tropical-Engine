#include <gl\glew.h>
#include "Shader.h"
#include "ShaderManager.h"


ShaderManager::ShaderManager(void)
{
}


ShaderManager::~ShaderManager(void)
{
	foreach(Shader* shader, shaders)
	{
		delete shader;
	}
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
	glUseProgram(shaders[name]->getShaderProgram());
}

void ShaderManager::UseShader(Shader* shader)
{
	glUseProgram(shader->getShaderProgram());
}
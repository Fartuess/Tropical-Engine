#include "Shader.h"

Shader* Shader::nullShader = nullptr;

Shader::Shader(QString vertexShader, QString fragmentShader, QString name):defaultMaterial(this, nullptr, name)
{
	///TODO: implement it.
}


Shader::~Shader(void)
{
	///TODO: implement it.
}

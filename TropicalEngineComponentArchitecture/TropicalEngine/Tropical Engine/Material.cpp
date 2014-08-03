#include "Shader.h"
#include "TextureManager.h"
#include "Material.h"
#include "MaterialManager.h"
#include "ModelComponent.h"
#include "ModelController.h"

#include "TropicalEngineApplication.h"

Material::Material(Shader* shader, void* params, QString name):parameters()
{
	this->name = name;
	this->shader = shader;
	foreach(QString parameterName, this->shader->getMaterialParameters().keys())
	{
		parameters.append(QPair<QString, void*>(parameterName, nullptr));
	}
	TropicalEngineApplication::instance()->materialManager->materials.insert(name, this);
}

Material::~Material(void)
{
	foreach(ModelComponent* modelComponent, TropicalEngineApplication::instance()->modelController->modelComponents)
	{
		if(modelComponent->material == this)
			modelComponent->material = this->getShader()->defaultMaterial;
	}
}

Shader* Material::getShader()
{
	return shader;
}

const QVector<QPair<QString, void*>>& Material::getParameters()
{
	return parameters;
}

void Material::Use()
{
	shader->Use();
	if(shader->getCurrentMaterial() != this)
	{
		typedef QPair<QString, void*> parameterType;
		foreach(parameterType parameter, parameters)
		{
			ActivateParameter(parameter.first, parameter.second);
		}
	}
}

void Material::ActivateParameter(QString name, void* value)
{
	TropicalEngineApplication::instance()->textureManager->resetTextureIterator();
	GLuint parameterLocation = shader->getParameterLocation(name);
	switch (shader->getParameterType(name))
	{
	case GL_FLOAT:
		ActivateParameter(parameterLocation, (float*)(value));
		break;
	case GL_FLOAT_VEC2:
		ActivateParameter(parameterLocation, (glm::vec2*)(value));
		break;
	case GL_FLOAT_VEC3:
		ActivateParameter(parameterLocation, (glm::vec3*)(value));
		break;
	case GL_FLOAT_VEC4:
		ActivateParameter(parameterLocation, (glm::vec4*)(value));
		break;
	case GL_FLOAT_MAT3:
		ActivateParameter(parameterLocation, (glm::mat3*)(value));
		break;
	case GL_FLOAT_MAT4:
		ActivateParameter(parameterLocation, (glm::mat4*)(value));
		break;
	case GL_SAMPLER_2D:
		ActivateParameter(parameterLocation, (Texture*)(value));
		break;
	default:
		break;
	}
}

void Material::ActivateParameter(GLuint location, float* value)
{
	glUniform1f(location, *value);
}

void Material::ActivateParameter(GLuint location, glm::vec2* value)
{
	glUniform2f(location, value->x, value->y);
}

void Material::ActivateParameter(GLuint location, glm::vec3* value)
{
	glUniform3f(location, value->x, value->y, value->z);
}

void Material::ActivateParameter(GLuint location, glm::vec4* value)
{
	glUniform4f(location, value->x, value->y, value->z, value->w);
}

void Material::ActivateParameter(GLuint location, glm::mat3* value)
{
	glUniformMatrix3fv(location, 1, false, (GLfloat*)value);
}

void Material::ActivateParameter(GLuint location, glm::mat4* value)
{
	glUniformMatrix4fv(location, 1, false, (GLfloat*)value);
}

void Material::ActivateParameter(GLuint location, Texture* value)
{
	value->ActivateTexture(location);
}

QString Material::toXML()
{
	///TODO: implement it.
	QString XMLString = QString(getIndent() + "<Material name = \"" + name + "\" shader = \"" + getShader()->name + "\">\n");
	increaseIndent();
	///TODO: save material parameters
	decreaseIndent();
	XMLString += QString(getIndent() + "</Material>\n");

	return XMLString;
}
#include "Shader\Shader.h"
#include "Texture\TextureManager.h"
#include "Shader\Material.h"
#include "Shader\MaterialManager.h"
#include "Model\ModelComponent.h"
#include "Model\ModelController.h"

#include "TropicalEngineApplication.h"

Material::Material(Shader* shader, void* params, QString name):parameters()	//params is not needed
{
	this->name = name;
	this->shader = shader;
	for (QString parameterName : this->shader->getMaterialParameters().keys())
	{
		parameters[parameterName] =  nullptr;
	}
	TropicalEngineApplication::instance()->materialManager->materials.insert(name, this);
}

Material::~Material(void)
{
	for (ModelComponent* modelComponent : TropicalEngineApplication::instance()->modelController->modelComponents)
	{
		if (modelComponent->material == this)
			modelComponent->material = this->getShader()->defaultMaterial;
	}
}

QString Material::getName()
{
	return name;
}

void Material::setName(QString name)
{
	///TODO: implement changing keynames in Material Managers.
	this->name = name;
}

Shader* Material::getShader()
{
	return shader;
}

//const QVector<QPair<QString, void*>>& Material::getParameters()
//{
//	return parameters;
//}

void Material::Use()
{
	shader->Use();
	TropicalEngineApplication::instance()->textureManager->resetTextureIterator();
	if (shader->getCurrentMaterial() != this)
	{
		//typedef QPair<QString, void*> parameterType;
		for (QString parameter : parameters.keys())
		{
			ActivateParameter(parameter, parameters[parameter]);
		}
	}
}

void Material::ActivateParameter(QString name, void* value)
{
	if (value == nullptr) return;

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

void Material::SetParameter(QString name, void* parameter)
{
	parameters[name] = parameter;
}

QString Material::toXML()
{
	///TODO: implement it.
	QString XMLString = QString(getIndent() + "<Material name = \"" + name + "\" shader = \"" + getShader()->getName() + "\">\n");
	increaseIndent();
	///TODO: save material parameters
	decreaseIndent();
	XMLString += QString(getIndent() + "</Material>\n");

	return XMLString;
}

QJsonObject Material::toJSON()
{
	QJsonObject JSON = QJsonObject();
	JSON["name"] = name;
	JSON["shader"] = shader->getName();

	QJsonArray materialParametersJSON = QJsonArray();
	for (QString materialParameter : parameters.keys())
	{
		QJsonObject materialParameterJSON = QJsonObject();
		materialParameterJSON["name"] = materialParameter;
		materialParameterJSON["type"] = QString::number(shader->getParameterType(materialParameter));
		QJsonObject valueJSON = QJsonObject();
		switch (shader->getParameterType(materialParameter))
		{
			case GL_FLOAT:
			{
				valueJSON["x"] = *((float*)(parameters[materialParameter]));
				break;
			}
			case GL_FLOAT_VEC2:
			{
				glm::vec2* value = (glm::vec2*)(parameters[materialParameter]);
				valueJSON["x"] = value->x;
				valueJSON["y"] = value->y;
				break;
			}
			case GL_FLOAT_VEC3:
			{
				glm::vec3* value = (glm::vec3*)(parameters[materialParameter]);
				valueJSON["x"] = value->x;
				valueJSON["y"] = value->y;
				valueJSON["z"] = value->z;
				break;
			}
			case GL_FLOAT_VEC4:
			{
				glm::vec4* value = (glm::vec4*)(parameters[materialParameter]);
				valueJSON["x"] = value->x;
				valueJSON["y"] = value->y;
				valueJSON["z"] = value->z;
				valueJSON["w"] = value->w;
				break;
			}
			case GL_FLOAT_MAT3:
			{
				glm::mat3* value = (glm::mat3*)(parameters[materialParameter]);
				QJsonArray matrixJSON = QJsonArray();
				QJsonArray x = QJsonArray();
				QJsonObject x1 = QJsonObject();
				QJsonObject x2 = QJsonObject();
				QJsonObject x3 = QJsonObject();
				x1["value"] = (*value)[0][0];
				x2["value"] = (*value)[0][1];
				x3["value"] = (*value)[0][2];
				x.push_back(x1);
				x.push_back(x2);
				x.push_back(x3);
				matrixJSON.push_back(x);
				QJsonArray y = QJsonArray();
				QJsonObject y1 = QJsonObject();
				QJsonObject y2 = QJsonObject();
				QJsonObject y3 = QJsonObject();
				y1["value"] = (*value)[1][0];
				y2["value"] = (*value)[1][1];
				y3["value"] = (*value)[1][2];
				y.push_back(y1);
				y.push_back(y2);
				y.push_back(y3);
				matrixJSON.push_back(y);
				QJsonArray z = QJsonArray();
				QJsonObject z1 = QJsonObject();
				QJsonObject z2 = QJsonObject();
				QJsonObject z3 = QJsonObject();
				z1["value"] = (*value)[2][0];
				z2["value"] = (*value)[2][1];
				z3["value"] = (*value)[2][2];
				z.push_back(z1);
				z.push_back(z2);
				z.push_back(z3);
				matrixJSON.push_back(z);
				valueJSON["matrix"] = matrixJSON;
				break;
			}
			case GL_FLOAT_MAT4:
			{
				glm::mat4* value = (glm::mat4*)(parameters[materialParameter]);
				QJsonArray matrixJSON = QJsonArray();
				QJsonArray x = QJsonArray();
				QJsonObject x1 = QJsonObject();
				QJsonObject x2 = QJsonObject();
				QJsonObject x3 = QJsonObject();
				QJsonObject x4 = QJsonObject();
				x1["value"] = (*value)[0][0];
				x2["value"] = (*value)[0][1];
				x3["value"] = (*value)[0][2];
				x4["value"] = (*value)[0][3];
				x.push_back(x1);
				x.push_back(x2);
				x.push_back(x3);
				x.push_back(x4);
				matrixJSON.push_back(x);
				QJsonArray y = QJsonArray();
				QJsonObject y1 = QJsonObject();
				QJsonObject y2 = QJsonObject();
				QJsonObject y3 = QJsonObject();
				QJsonObject y4 = QJsonObject();
				y1["value"] = (*value)[1][0];
				y2["value"] = (*value)[1][1];
				y3["value"] = (*value)[1][2];
				y4["value"] = (*value)[1][3];
				y.push_back(y1);
				y.push_back(y2);
				y.push_back(y3);
				y.push_back(y4);
				matrixJSON.push_back(y);
				QJsonArray z = QJsonArray();
				QJsonObject z1 = QJsonObject();
				QJsonObject z2 = QJsonObject();
				QJsonObject z3 = QJsonObject();
				QJsonObject z4 = QJsonObject();
				z1["value"] = (*value)[2][0];
				z2["value"] = (*value)[2][1];
				z3["value"] = (*value)[2][2];
				z3["value"] = (*value)[2][3];
				z.push_back(z1);
				z.push_back(z2);
				z.push_back(z3);
				z.push_back(z4);
				matrixJSON.push_back(z);
				QJsonArray w = QJsonArray();
				QJsonObject w1 = QJsonObject();
				QJsonObject w2 = QJsonObject();
				QJsonObject w3 = QJsonObject();
				QJsonObject w4 = QJsonObject();
				w1["value"] = (*value)[3][0];
				w2["value"] = (*value)[3][1];
				w3["value"] = (*value)[3][2];
				w3["value"] = (*value)[3][3];
				w.push_back(w1);
				w.push_back(w2);
				w.push_back(w3);
				w.push_back(w4);
				matrixJSON.push_back(w);
				valueJSON["matrix"] = matrixJSON;
				break;
			}
			case GL_SAMPLER_2D:
			{
				valueJSON["name"] = ((Texture*)(parameters[materialParameter]))->getName();
				break;
			}
			default:
			{
				break;
			}
		}
		materialParameterJSON["value"] = valueJSON;
		materialParametersJSON.push_back(materialParameterJSON);
	}
	JSON["parameters"] = materialParametersJSON;

	return JSON;
}
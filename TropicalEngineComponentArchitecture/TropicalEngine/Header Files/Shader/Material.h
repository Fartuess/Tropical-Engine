#pragma once
#include <glm.hpp>
#include <QtCore\qvector.h>
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

class Shader;
class Texture;

class Material : public ISerializableToXML, public ISerializableToJSON
{
private:
	QString name;
public:
	QString getName();
	void setName(QString name);
private:
	Shader* shader;
	QMap<QString, void*> parameters;
public:
	Material(Shader* shader, void* params, QString name);	///TODO: Rethink constructor.
	~Material(void);

	Shader* getShader();
	///TODO: figure out if it is easy to implement parameter get and getAll
	//const QVector<QPair<QString, void*>>& getParameters();
	void Use();

	void ActivateParameter(QString name, void* value);
private:
	void ActivateParameter(GLuint location, float* value);
	void ActivateParameter(GLuint location, glm::vec2* value);
	void ActivateParameter(GLuint location, glm::vec3* value);
	void ActivateParameter(GLuint location, glm::vec4* value);
	void ActivateParameter(GLuint location, glm::mat3* value);
	void ActivateParameter(GLuint location, glm::mat4* value);
	void ActivateParameter(GLuint location, Texture* value);
public:
	void SetParameter(QString name, void* parameter);

	QString toXML() override;
	QJsonObject toJSON() override;
};


#pragma once
#include <glm.hpp>
#include <QtCore\qvector.h>
#include "ISerializableToXML.h"

class Shader;
class Texture;

class Material : public ISerializableToXML
{
public:
	QString name;	///TODO: should not be public. Should have getters and setters, because changing internal name doesn't change name in material manager
private:
	Shader* shader;
	QMap<QString, void*> parameters;
public:
	Material(Shader* shader, void* params, QString name);	//temp declaration
	~Material(void);

	Shader* getShader();
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
};


#pragma once
#include <glm.hpp>

#include <QtCore/qvector.h>

#include <Serialization/ISerializableJSON.h>

#include "MaterialParameter.h"

class Material : public ISerializableJSON
{
public:
	QString getName();
	void setName(QString name);

	Material(class Shader* shader, QString name);
	~Material(void);

	class Shader* getShader();

	void Use();
	
	void ActivateParameter(QString name, void* value);

	void SetParameter(QString name, void* parameter);

	MaterialParameter& operator[](QString name)      { return parameters[name]; };
	const MaterialParameter& operator[](QString name) const { return parameters[name]; };

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	QString name;
	class Shader* shader;
	QMap<QString, MaterialParameter> parameters;

private:
	void ActivateParameter(GLuint location, float* value);
	void ActivateParameter(GLuint location, glm::vec2* value);
	void ActivateParameter(GLuint location, glm::vec3* value);
	void ActivateParameter(GLuint location, glm::vec4* value);
	void ActivateParameter(GLuint location, glm::mat3* value);
	void ActivateParameter(GLuint location, glm::mat4* value);
	void ActivateParameter(GLuint location, class Texture* value);
};


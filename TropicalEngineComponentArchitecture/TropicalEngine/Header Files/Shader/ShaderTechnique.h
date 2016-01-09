#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	class ShaderTechnique : public ISerializableJSON
	{
	public:
		TYPENAME(ShaderTechnique)

		ShaderTechnique(QString name, class AbstractShaderBuilder* shaderBuilder, bool managed = true);
		ShaderTechnique(QString name, class Shader* shader, QString shaderPass = "Default", bool managed = true);
		~ShaderTechnique();

		QString getName()	{ return name; };
		void setName(QString name)	{ this->name = name; };
		void setInput(QString name, QString path);
		//void addShaderPass(QString name, class Shader* shader);
		class Shader* getShader(QString shaderPass = "Default");
		class Shader* generateShader(QString shaderPass = "Default");
		//class Shader* generateShaders();

		QJsonObject toJSON() override;
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	protected:
		QString name;
		bool isManaged;
		class AbstractShaderBuilder* shaderBuilder;
		QMap<QString, class Shader*> shaderPasses;

		QMap<QString, QString> inputs;
	};

}
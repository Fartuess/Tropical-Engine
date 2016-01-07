#pragma once

#include <QtCore/qstring.h>
#include <QtCore/qmap.h>

namespace TropicalEngine
{

	class ShaderTechnique
	{
	public:
		ShaderTechnique(QString name, class AbstractShaderBuilder* shaderBuilder, bool managed = true);
		~ShaderTechnique();

		QString getName()	{ return name; };
		void setName(QString name)	{ this->name = name; };
		void setInput(QString name, QString path);
		//void addShaderPass(QString name, class Shader* shader);
		class Shader* getShader(QString shaderPass = "Default");
		class Shader* generateShader(QString shaderPass = "Default");
		//class Shader* generateShaders();

	protected:
		QString name;
		bool isManaged;
		class AbstractShaderBuilder* shaderBuilder;
		QMap<QString, class Shader*> shaderPasses;
	};

}